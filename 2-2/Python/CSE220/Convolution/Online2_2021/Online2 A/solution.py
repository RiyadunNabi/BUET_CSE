import numpy as np
import os

# --- Helper: Create dummy input.txt for demonstration ---
# (You can remove this block if you already have the file)
input_content = """10,11,12,9,10,13,15,16,17,18
3
0.8"""
with open("input.txt", "w") as f:
    f.write(input_content)
# --------------------------------------------------------

def solve_library_convolve():
    # 1. Read input from input.txt
    # The format is strictly defined:
    # Line 1: Comma separated prices
    # Line 2: Window size (n)
    # Line 3: Alpha
    try:
        with open("input.txt", "r") as file:
            lines = file.readlines()
            
        # Parse Line 1: Stock Prices
        price_list = list(map(int, lines[0].strip().split(',')))
        
        # Parse Line 2: Window size
        n = int(lines[1].strip())
        
        # Parse Line 3: Alpha
        alpha = float(lines[2].strip())

    except FileNotFoundError:
        print("Error: input.txt not found.")
        return

    # 2. Define the Impulse Response Function h[k] [cite: 11]
    # h[k] = alpha * (1 - alpha)^k
    # We need k from 0 to n-1 [cite: 50]
    # This creates the weights: [alpha, alpha*(1-alpha), alpha*(1-alpha)^2 ...]
    k_indices = np.arange(n)
    h = alpha * np.power((1 - alpha), k_indices)

    # 3. Perform Convolution [cite: 16]
    # We use mode='valid' to get exactly m-n+1 outputs [cite: 24]
    # This mode ensures the convolution is only computed where the signals fully overlap.
    exsm = np.convolve(price_list, h, mode='valid')

    # 4. Print Output in the specified format [cite: 36]
    formatted_output = ", ".join(f"{num:.2f}" for num in exsm)
    print("Exponential Smoothing: " + formatted_output)

    # --------------------------------------------------------

def manual_convolution_valid(signal, impulse_response):
    """
    Performs convolution manually without using library functions like np.convolve.
    Implements the formula: y[n] = Sum( x[k] * h[n-k] )
    
    Args:
        signal (list): The stock prices (x)
        impulse_response (list): The weighting function (h)
        
    Returns:
        list: The convolved signal (valid mode only)
    """
    sig_len = len(signal)
    win_len = len(impulse_response)
    
    # We need exactly m - n + 1 outputs [cite: 24]
    output_len = sig_len - win_len + 1
    result = []

    # Slide the window across the signal
    for i in range(output_len):
        current_window = signal[i : i + win_len]
   
        window_sum = 0
        for j in range(win_len):
            val = current_window[j] * impulse_response[win_len - 1 - j]
            window_sum += val
            
        result.append(window_sum)
        
    return result

def solve_manual():
    # 1. Read input from input.txt
    try:
        with open("input.txt", "r") as file:
            lines = file.readlines()
            # [cite: 21] Line 1: Stock prices (m integers)
            price_list = list(map(int, lines[0].strip().split(',')))
            # [cite: 22] Line 2: Window size n
            n = int(lines[1].strip())
            # [cite: 23] Line 3: Alpha
            alpha = float(lines[2].strip())
    except FileNotFoundError:
        print("Error: input.txt not found.")
        return

    # 2. Define the Impulse Response Function h[k]
    # Formula: h[k] = alpha * (1 - alpha)^k [cite: 11]
    # We need k from 0 to n-1 [cite: 50]
    # h = []
    # for k in range(n):
    #     val = alpha * ((1 - alpha) ** k)
    #     h.append(val)

    # NumPy version (vectorized, correct way)
    k = np.arange(n)
    h = alpha * (1 - alpha) ** k
    
    # # If you REALLY want a loop (learning only)
    # h = np.zeros(n)
    # for k in range(n):
    # h[k] = alpha * (1 - alpha) ** k
    # # But in real code? ❌ Avoid.

    # 3. Perform Exponential Smoothing using Convolution
    # [cite: 16] "You must make use of convolution to solve this problem"
    exsm = manual_convolution_valid(price_list, h)

    # 4. Print Output
    # [cite: 24] Output format: m-n+1 values
    formatted_output = ", ".join(f"{num:.2f}" for num in exsm)
    print("Exponential Smoothing: " + formatted_output)

if __name__ == "__main__":
    solve_library_convolve()
    solve_manual()