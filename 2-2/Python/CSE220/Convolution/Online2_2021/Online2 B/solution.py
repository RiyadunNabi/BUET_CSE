import sys
import numpy as np

# --- 1. Manual Convolution Function ---
# Strictly prohibited from using np.convolve, so we implement the math manually.
# Formula: y[n] = Sum( x[k] * h[n-k] )
def manual_convolution_valid(signal, impulse_response):
    """
    Performs convolution manually.
    Args:
        signal (list): The stock prices (x)
        impulse_response (list): The weighting function (h)
    Returns:
        list: The convolved signal (valid mode only)
    """
    sig_len = len(signal)
    win_len = len(impulse_response)
    
    # Valid mode output length: m - n + 1
    output_len = sig_len - win_len + 1
    result = []

    # Slide the window
    for i in range(output_len):
        current_window = signal[i : i + win_len]
        
        # Calculate convolution sum
        val = 0
        for j in range(win_len):
            val += current_window[j] * impulse_response[win_len - 1 - j]
            
        result.append(val)
        
    return result

def solve():
    # --- 2. Input Handling ---
    # Case 1 Sample Input style
    try:
        # Taking input from standard input (console)
        # Assuming input format:
        # 1, 2, 3, 4, 5, 6, 7, 8 (or space separated)
        # 4
        
        line1 = input("Stock Prices: ")
        # Handle both comma-separated or space-separated inputs
        if ',' in line1:
            price_list = list(map(int, line1.replace("Stock Prices:", "").strip().split(',')))
        else:
            price_list = list(map(int, line1.replace("Stock Prices:", "").strip().split()))
            
        line2 = input("Window size: ")
        n = int(line2.replace("Window size:", "").strip())
        
    except ValueError:
        print("Invalid Input Format.")
        return

    # --- 3. Unweighted Moving Average ---
    # Logic: All weights are equal (1/n).
    # Impulse Response h: [1/n, 1/n, ..., 1/n]
    # h_unweighted = [1.0 / n] * n
    
    #using numpy, better
    h_unweighted = np.full(n, 1.0/n)
    
    # Compute
    res_unweighted = manual_convolution_valid(price_list, h_unweighted)

    # --- 4. Weighted Moving Average ---
    # Logic: Weights are 1, 2, ..., n.
    # Normalization factor S = sum(1 to n) = n(n+1)/2
    # The problem requires the *last* day (latest price) to have weight n.
    # Due to convolution flipping the kernel, we must define h in DESCENDING order
    # so that when flipped, the weights become ASCENDING [1, 2, ..., n].
    
    # Calculate sum of weights for normalization
    total_weight = n * (n + 1) / 2
    
    h_weighted = []
    # Generate weights: n, n-1, ..., 1 (Descending)
    for k in range(n):
        weight = n - k
        h_weighted.append(weight / total_weight)

    # # np.arange(start, stop, step)
    # weights = np.arange(n, 0, -1) #or these using numpy
    # h_weighted = weights / np.sum(weights)
    
    # Compute
    res_weighted = manual_convolution_valid(price_list, h_weighted)

    # --- 5. Output Formatting ---
    print("Unweighted Moving Average: " + ", ".join(f"{num:.2f}" for num in res_unweighted))
    print("Weighted Moving Average: " + ", ".join(f"{num:.2f}" for num in res_weighted))

##################################################################################
###USING NUMPY

def manual_convolution_numpy(signal, kernel):
    n_sig = signal.size
    n_ker = kernel.size
    n_out = n_sig - n_ker + 1
    output = np.zeros(n_out)
    kernel_flipped = kernel[::-1]
    for i in range(n_out):
        window = signal[i : i + n_ker]
        output[i] = np.sum(window * kernel_flipped)
    return output

def solve_numpy():
    try:
        line1 = input()
        if ":" in line1:
            line1 = line1.split(":")[1]
        prices = np.fromstring(line1.replace(",", " "), sep=" ")
        
        line2 = input()
        if ":" in line2:
            line2 = line2.split(":")[1]
        n = int(line2)
    except:
        return

    h_unweighted = np.full(n, 1.0/n)
    
    weights = np.arange(n, 0, -1)
    h_weighted = weights / np.sum(weights)

    res_unweighted = manual_convolution_numpy(prices, h_unweighted)
    res_weighted = manual_convolution_numpy(prices, h_weighted)

    print("Unweighted Moving Average: " + ", ".join(f"{x:.2f}" for x in res_unweighted))
    print("Weighted Moving Average: " + ", ".join(f"{x:.2f}" for x in res_weighted))
##################################################################################
###

if __name__ == "__main__":
    solve()
    solve_numpy()