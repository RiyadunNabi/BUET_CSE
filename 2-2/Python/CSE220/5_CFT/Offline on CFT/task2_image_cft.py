import numpy as np
import matplotlib.pyplot as plt
from imageio import imread

# =====================================================
# Continuous Image Class
# =====================================================
class ContinuousImage:
    """
    Represents an image as a continuous 2D signal.
    """

    def __init__(self, image_path):
        self.image = imread(image_path, mode='L')
        self.image = self.image / np.max(self.image)

        # Define continuous spatial axes
        self.x = np.linspace(-1, 1, self.image.shape[1])
        self.y = np.linspace(-1, 1, self.image.shape[0])

    def show(self, title="Image"):
        plt.imshow(self.image, cmap='gray')
        plt.title(title)
        plt.axis('off')
        plt.show()


# =====================================================
# 2D Continuous Fourier Transform Class
# =====================================================
class CFT2D:
    """
    Computes 2D Continuous Fourier Transform
    using separability and numerical integration.
    """

    def __init__(self, image_obj:ContinuousImage):
        self.I = image_obj.image
        self.x = image_obj.x
        self.y = image_obj.y

        self.u = self.x 
        self.v = self.y


    def compute_cft(self):
        """
        Compute real and imaginary parts of 2D CFT.
        """
        I_expanded = self.I[:, :, np.newaxis]

        #F(u) = Integral( I(x) * exp(-j.w.x) ) dx    w=2.pi.u
        x_expanded = self.x[np.newaxis, :, np.newaxis]
        u_expanded = self.u[np.newaxis, np.newaxis, :]
        arg_x = 2 * np.pi * u_expanded * x_expanded
        H_real = np.trapz(I_expanded * np.cos(arg_x), self.x, axis=1)
        H_imag = np.trapz(I_expanded * -np.sin(arg_x), self.x, axis=1)

        H_real_exp = H_real[:, np.newaxis, :]
        H_imag_exp = H_imag[:, np.newaxis, :]
        y_expanded = self.y[:, np.newaxis, np.newaxis]
        v_expanded = self.v[np.newaxis, :, np.newaxis]
        arg_y = 2 * np.pi * v_expanded * y_expanded
        cos_y = np.cos(arg_y)
        sin_y = np.sin(arg_y)
        integrand_real = H_real_exp * cos_y + H_imag_exp * sin_y
        integrand_imag = -H_real_exp * sin_y + H_imag_exp * cos_y
        self.F_real = np.trapz(integrand_real, self.y, axis=0)
        self.F_imag = np.trapz(integrand_imag, self.y, axis=0)
        
        return self.F_real, self.F_imag

    def plot_magnitude(self):
        """
        Plot log-scaled magnitude spectrum.
        """
        magnitude = np.sqrt(self.F_real**2 + self.F_imag**2)
        log_mag = np.log(magnitude + 1)
        
        plt.figure(figsize=(6, 6))
        plt.imshow(log_mag, cmap='inferno', extent=[self.u[0], self.u[-1], self.v[-1], self.v[0]])
        plt.title("2D CFT Magnitude Spectrum (Log Scale)")
        plt.colorbar()
        plt.show()


# =====================================================
# Frequency Filtering
# =====================================================
class FrequencyFilter:
    def low_pass(self, real, imag, cutoff):
        rows, cols = real.shape
        cx, cy = rows//2, cols//2

        for i in range(rows):
            for j in range(cols):
                if np.sqrt((i-cx)**2 + (j-cy)**2) > cutoff:
                    real[i,j] = 0
                    imag[i,j] = 0
        return real, imag

# =====================================================
# Inverse 2D Continuous Fourier Transform
# =====================================================
class InverseCFT2D:
    """
    Reconstructs image from 2D frequency spectrum.
    """

    def __init__(self, real, imag, x, y):
        self.real=real 
        self.imag = imag
        self.x = x
        self.y = y

    def reconstruct(self):
        """
        Perform inverse 2D CFT using numerical integration.
        """
        F_real_exp = self.real[:, :, np.newaxis] 
        F_imag_exp = self.imag[:, :, np.newaxis]
        v_expanded = self.y[:, np.newaxis, np.newaxis] 
        y_out_expanded = self.y[np.newaxis, np.newaxis, :]
        
        arg_v = 2 * np.pi * v_expanded * y_out_expanded
        
        integrand_v_real = F_real_exp * np.cos(arg_v) - F_imag_exp * np.sin(arg_v)
        integrand_v_imag = F_real_exp * np.sin(arg_v) + F_imag_exp * np.cos(arg_v)
        
        G_real = np.trapz(integrand_v_real, self.y, axis=0) 
        G_imag = np.trapz(integrand_v_imag, self.y, axis=0)
        
        G_real = G_real.T
        G_imag = G_imag.T
        
        G_real_exp = G_real[:, :, np.newaxis] 
        G_imag_exp = G_imag[:, :, np.newaxis]
        u_expanded = self.x[np.newaxis, :, np.newaxis]
        x_out_expanded = self.x[np.newaxis, np.newaxis, :] 
        
        arg_u = 2 * np.pi * u_expanded * x_out_expanded
        
        integrand_u_real = G_real_exp * np.cos(arg_u) - G_imag_exp * np.sin(arg_u)
        
        I_reconstructed = np.trapz(integrand_u_real, self.x, axis=1)
        
        return I_reconstructed


# =====================================================
# Main Execution (Task 2)
# =====================================================
img = ContinuousImage("Offline on CFT/noisy_image.png")
img.show("Original Image")

cft2d = CFT2D(img)
real, imag = cft2d.compute_cft()
cft2d.plot_magnitude()

filt = FrequencyFilter()
real_f, imag_f = filt.low_pass(real, imag, cutoff=40)

icft2d = InverseCFT2D(real_f, imag_f, img.x, img.y)
denoised = icft2d.reconstruct()

plt.imshow(denoised, cmap='gray')
plt.title("Reconstructed (Denoised) Image")
plt.axis('off')
plt.show()
