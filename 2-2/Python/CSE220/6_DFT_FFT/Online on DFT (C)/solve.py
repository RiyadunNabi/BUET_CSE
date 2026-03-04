import cv2
import numpy as np
import math

def fft(x):
    """
    Compute 1D FFT using Radix-2 Decimation-in-Time (DIT) algorithm.
    Pads to the next power of 2 if necessary to ensure O(N log N) performance.
    """
    x = np.asarray(x, dtype=np.complex128)
    N = len(x)
    
    if N <= 1:
        return x
    
    # Pad to next power of 2 if N is not a power of 2
    if (N & (N - 1)) != 0:
        next_pow2 = 1 << (N - 1).bit_length()
        x = np.pad(x, (0, next_pow2 - N), 'constant')
        N = next_pow2
        
    even = fft(x[0::2])
    odd = fft(x[1::2])
    
    # Twiddle factors
    factor = np.exp(-2j * np.pi * np.arange(N // 2) / N)
    
    return np.concatenate([even + factor * odd, even - factor * odd])

def ifft(X):
    """
    Compute 1D inverse FFT using the FFT function based on the property:
    IFFT(X) = 1/N * conj(FFT(conj(X)))
    """
    X = np.asarray(X, dtype=np.complex128)
    N = len(X)
    
    X_conj = np.conj(X)
    x = fft(X_conj)
    x = np.conj(x) / N
    
    return x

def reconstruct_image_using_fft(original_path, shifted_path, output_path):
    
    original_img = cv2.imread(original_path)
    shifted_img = cv2.imread(shifted_path)

    if original_img is None or shifted_img is None:
        print("Error: Could not load images.")
        return

    if original_img.shape != shifted_img.shape:
        print("Error: Image dimensions do not match.")
        return
    
    # Convert the original and shifted color images to grayscale for processing.
    orig_gray = cv2.cvtColor(original_img, cv2.COLOR_BGR2GRAY)
    shift_gray = cv2.cvtColor(shifted_img, cv2.COLOR_BGR2GRAY)
    #===============================================================
    # Prepare an empty array for the reconstructed color image
    reconstructed_img = np.zeros_like(shifted_img)
    rows, cols = orig_gray.shape

    print("Reconstructing image using manual FFT...")
    # $$R_{xy} = \text{IFFT}(\text{FFT}(x)^* \cdot \text{FFT}(y))$$
    for i in range(rows):
        orig_row = orig_gray[i, :]
        shift_row = shift_gray[i, :]
        
        # 1. Compute FFT of both rows
        O_f = fft(orig_row)
        S_f = fft(shift_row)
        
        # 2. Compute Cross-Power Spectrum
        # R_xy = conj(FFT(x)) * FFT(y)
        cross_spec = np.conj(O_f) * S_f
        
        # 3. Compute Inverse FFT to get Cross-Correlation
        cross_corr = ifft(cross_spec)
        
        # 4. Find the shift amount (index of the maximum peak in real part)
        # We only search up to 'cols' because our FFT might have padded the array 
        # to a larger power of 2 length.
        cross_corr_real = np.real(cross_corr[:cols])
        shift_amount = np.argmax(cross_corr_real)
        
        # 5. Reverse the shift on the *Color* image row
        # If the row was shifted right by 'shift_amount', we roll it left by '-shift_amount'
        reconstructed_img[i] = np.roll(shifted_img[i], -shift_amount, axis=0)

    # Calculate MSE to verify exact reconstruction
    mse = np.mean((original_img - reconstructed_img) ** 2)
    print(f"Reconstruction Complete! Mean Squared Error vs Original: {mse:.4f}")
    if mse < 1e-5:
        print("Success! Reconstructed image matches the original perfectly.")

    cv2.imwrite(output_path, reconstructed_img)
    print(f"Saved reconstructed image to: {output_path}")
    
if __name__ == "__main__":
    reconstruct_image_using_fft("original_image.png", "shifted_image.jpg", "reconstructed_image_fft.jpg")