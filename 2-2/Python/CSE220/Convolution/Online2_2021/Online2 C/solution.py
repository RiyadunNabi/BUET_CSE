import numpy as np
import sys

def manual_convolution_full(signal, kernel):
    # Get sizes
    n_sig = signal.size
    n_ker = kernel.size
    
    # Result length for full convolution is N + M - 1
    n_out = n_sig + n_ker - 1
    
    # Initialize output array with zeros
    output = np.zeros(n_out, dtype=int)
    
    # Perform Convolution Sum: y[n] = Sum(x[k] * h[n-k])
    # We iterate through every output index n
    for n in range(n_out):
        # Determine the valid range of k to avoid index out of bounds
        # We need: 0 <= k < n_sig  AND  0 <= n - k < n_ker
        # Solving for k:
        # 1. k >= 0
        # 2. k < n_sig
        # 3. k <= n
        # 4. k > n - n_ker  =>  k >= n - n_ker + 1
        
        start_k = max(0, n - n_ker + 1)
        end_k = min(n_sig - 1, n)
        
        # Calculate sum for this output position
        # We can use numpy slicing to speed up the inner sum
        # indices for signal: k ranges from start_k to end_k
        # indices for kernel: (n-k) ranges correspondingly
        
        if start_k <= end_k:
            # Create index arrays for vectorized multiplication
            k_indices = np.arange(start_k, end_k + 1)
            h_indices = n - k_indices
            
            # Element-wise multiply and sum
            output[n] = np.sum(signal[k_indices] * kernel[h_indices])
            
    return output

def solve():
    try:
        # --- Input Parsing using NumPy helpers ---
        # Parse Line 1: Degree 1 (Not strictly needed for calculation, but part of input)
        line = input().split(":")
        d1 = int(line[-1].strip())

        # Parse Line 2: Coeffs 1
        line = input().split(":")
        # np.fromstring is faster and cleaner for space-separated numbers
        coeffs1 = np.fromstring(line[-1], sep=" ", dtype=int)

        # Parse Line 3: Degree 2
        line = input().split(":")
        d2 = int(line[-1].strip())

        # Parse Line 4: Coeffs 2
        line = input().split(":")
        coeffs2 = np.fromstring(line[-1], sep=" ", dtype=int)

    except (ValueError, IndexError):
        return

    # --- Perform Polynomial Multiplication ---
    result_coeffs = manual_convolution_full(coeffs1, coeffs2)
    
    # Calculate new degree
    deg_out = result_coeffs.size - 1
    
    # --- Output Formatting ---
    print(f"Degree of the Polynomial: {deg_out}")
    
    # Format coefficients using numpy
    print("Coefficients: " + " ".join(result_coeffs.astype(str)))

if __name__ == "__main__":
    solve()