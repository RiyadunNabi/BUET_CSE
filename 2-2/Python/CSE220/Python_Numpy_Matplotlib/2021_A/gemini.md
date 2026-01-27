CSE220 Signals and Linear Systems
Online on Signal Basics

14 September 2024

Time: 30 min
Read the entire instruction carefully before starting to code.

1 Introduction
In this online, your task is to implement the following functions for discrete
signals
1. time shift signal
2. time scale signal
2 Representing Discrete Signal
We will represent a discrete signal as a numpy array. We will assume that all
signals extend from −∞ to ∞, but the numpy array will only contain the signal
values from −8 to 8. Signal values outside this range is considered to be 0.
For example, the array x = [0, 0, 0, 0, 0, 0, 0.5, 2, 1, 0.5, 1, 0, 0, 0, 0, 0, 0] represents
the signal x[n] in figure 1.

Figure 1: Signal corresponding to [0, 0, 0, 0, 0, 0, 0.5, 2, 1, 0.5, 1, 0, 0, 0, 0, 0, 0]

1

3 Tasks
You are provided with a python file. In this file, you have to implement 2
functions.
3.1 Task 1
Implement: time shift signal(x,k)
Input Parameters:
• x: A numpy array representing a discrete signal.
• k: An integer, −8 ≤ k ≤ 8. The number of units the signal is to be shifted.
The function should return a numpy array representing the shifted signal x[n-k].
Example: Shifting the signal x of figure 1 by 2 units to right would give the
signal in figure 2.

Figure 2: x[n − 2]

3.2 Task 2
Function to be implemented: time scale signal(x,k)
Input Parameters:
• x: A numpy array representing a discrete signal.
• k: A positive integer.
The function should return a numpy array representing the time scaled signal
x[kn] Example: see figure 3
3.3 Bonus Task
You will get bonus marks if you can complete the tasks using numpy functions
rather than using explicit python loops.

2

Figure 3: x[2n]

4 Mark Distribution
See table 1

Task 1 4
Task 2 6
Bonus 2

Table 1: Mark Distribution

---
---
---
---
Here is the complete solution for your **CSE220 Signals and Linear Systems** assignment.

---

### **2. Complete Solution Code**

Here is the full code. I have filled in the two functions using **NumPy** for the bonus marks.

```python
import numpy as np
import matplotlib.pyplot as plt

INF = 8

def plot(
        signal, 
        title=None, 
        y_range=(-1, 3), 
        figsize = (8, 3),
        x_label='n (Time Index)',
        y_label='x[n]',
        saveTo=None
    ):
    plt.figure(figsize=figsize)
    plt.xticks(np.arange(-INF, INF + 1, 1))
    
    y_range = (y_range[0], max(np.max(signal), y_range[1]) + 1)
    plt.ylim(*y_range)
    plt.stem(np.arange(-INF, INF + 1, 1), signal)
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.grid(True)
    if saveTo is not None:
        plt.savefig(saveTo)
    plt.show()

def init_signal():
    return np.zeros(2 * INF + 1)

# ---------------------------------------------------------
# Solution Starts Here
# ---------------------------------------------------------

def time_shift_signal(x: np.ndarray, k: int) -> np.ndarray:
    """
    Returns x[n - k].
    Using np.roll for shifting and masking for zero-padding.
    """
    if k == 0:
        return x.copy()
    
    # Shift the array elements
    shifted = np.roll(x, k)
    
    # Fix the boundary conditions (replace wrapped values with 0)
    if k > 0:
        # Right shift: The first k elements should be 0
        shifted[:k] = 0
    else:
        # Left shift (k is negative): The last abs(k) elements should be 0
        shifted[k:] = 0
        
    return shifted

def time_scale_signal(x: np.ndarray, k: int) -> np.ndarray:
    """
    Returns x[k * n].
    Using vectorized indexing (Bonus Task approach).
    """
    if k == 0:
        # Edge case: x[0] everywhere? Usually k is positive integer >= 1.
        # But per instruction, k is a positive integer.
        return np.zeros_like(x)

    # 1. Create the output array of zeros
    y = np.zeros_like(x)
    
    # 2. Define the range of n (-8 to 8)
    n = np.arange(-INF, INF + 1)
    
    # 3. Determine which n values result in valid indices for x
    # We need x[k*n]. The time index 'k*n' must be within [-INF, INF]
    valid_mask = np.abs(n * k) <= INF
    
    # 4. Extract the valid n values
    valid_n = n[valid_mask]
    
    # 5. Map indices
    # Output index for time n is: INF + n
    # Input index for time k*n is: INF + k*n
    y[INF + valid_n] = x[INF + valid_n * k]
    
    return y

# ---------------------------------------------------------
# Main Driver Code
# ---------------------------------------------------------

def main():
    img_root_path = '.'
    signal = init_signal()
    
    # Setting up the signal as per Figure 1 description
    # x = [..., 0.5, 2, 1, 0.5, 1, ...]
    # Center (Index 8) is 1.
    signal[INF] = 1       # n=0
    signal[INF+1] = 0.5   # n=1
    signal[INF-1] = 2     # n=-1
    signal[INF-2] = 0.5   # n=-2
    signal[INF+2] = 1     # n=2 (Added based on Fig 1 logic if needed, or stick to provided template)
    # Note: The provided template in your set1.py had explicit values:
    # signal[INF] = 1, signal[INF+1] = .5, signal[INF-1] = 2, signal[INF+2]=1, signal[INF-2]=.5
    # I will stick to the template logic.
    
    plot(signal, title='Original Signal x[n]', saveTo=f'{img_root_path}/x[n].png')

    # Task 1: Shifts
    plot(time_shift_signal(signal, 2), title='x[n-2] (Right Shift)', saveTo=f'{img_root_path}/x[n-2].png')
    plot(time_shift_signal(signal, -2), title='x[n+2] (Left Shift)', saveTo=f'{img_root_path}/x[n+2].png')
    plot(time_shift_signal(signal, 0), title='x[n+0] (No Shift)', saveTo=f'{img_root_path}/x[n+0].png')
    
    # Task 2: Scales
    plot(time_scale_signal(signal, 2), title='x[2n] (Decimation)', saveTo=f'{img_root_path}/x[2n].png')
    plot(time_scale_signal(signal, 1), title='x[1n] (Original)', saveTo=f'{img_root_path}/x[1n].png')

if __name__ == "__main__":
    main()

```

---

### **3. Explanation of Changes**

#### **For `time_shift_signal(x, k)**`

* **Original:** `None`
* **New Code:**
```python
shifted = np.roll(x, k)
if k > 0: shifted[:k] = 0
else: shifted[k:] = 0
return shifted

```


* **Why:** `np.roll` moves the data but "wraps around" (values falling off the right side reappear on the left). Since a signal is 0 at infinity, we must overwrite those wrapped values with 0.

#### **For `time_scale_signal(x, k)**`

* **Original:** `None`
* **New Code:**
```python
valid_mask = np.abs(n * k) <= INF
valid_n = n[valid_mask]
y[INF + valid_n] = x[INF + valid_n * k]

```


* **Why:** This uses **Vectorization** (bonus marks).
* We create an array of all time indices `n` from -8 to 8.
* `valid_mask` checks if scaling `n` by `k` keeps us inside the array boundaries.
* `y[INF + valid_n] = x[INF + valid_n * k]` maps the values directly in one step without using a `for` loop.