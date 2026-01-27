Here is the complete guide to **Time Operations** (Shifting, Scaling, Reversal) for both **Discrete Time (DT)** and **Continuous Time (CT)** using NumPy.

---

### **Part 1: Discrete Time (DT) Operations**

**Key Concept:** In discrete time, the "time" is actually an **integer index**.

1. **Shift ():** We move elements in the array.
2. **Scale ():** We skip elements (Decimation) or insert zeros (Interpolation).
3. **Reverse ():** We flip the array order.

```python
import numpy as np
import matplotlib.pyplot as plt

# --- 1. SETUP: Create a Discrete Signal ---
# Let's say our signal is defined from n = -5 to 5
n = np.arange(-5, 6) 
x = np.array([0, 0, 0, 1, 2, 3, 2, 1, 0, 0, 0]) # A simple triangle pulse

def plot_dt(n, x, title):
    plt.figure(figsize=(6, 2))
    plt.stem(n, x)
    plt.title(title)
    plt.grid(True)
    plt.show()

plot_dt(n, x, "Original Discrete Signal x[n]")

# --- 2. TIME REVERSAL: x[-n] ---
# Just reverse the array using slicing
x_reversed = x[::-1]
plot_dt(n, x_reversed, "Time Reversal x[-n]")


# --- 3. TIME SHIFT: x[n - k] ---
# A shift of k=2 (Right Shift).
# Logic: We roll the array, then fill the empty space with zeros.
k = 2
x_shifted = np.roll(x, k)
if k > 0:
    x_shifted[:k] = 0   # Clear the beginning (Right shift)
else:
    x_shifted[k:] = 0   # Clear the end (Left shift)

plot_dt(n, x_shifted, f"Time Shift x[n - {k}]")


# --- 4. TIME SCALING (Downsampling): x[k*n] ---
# We keep only every k-th sample.
scale_factor = 2
# This logic assumes the array is centered. 
# A simple way for beginners is strictly slicing:
x_scaled = x[::scale_factor] 
# Note: The time axis 'n' also shrinks!
n_scaled = n[::scale_factor]

plot_dt(n_scaled, x_scaled, f"Time Scaling x[{scale_factor}n]")

#--- 3.1 USING LOOP ---
def time_scale_signal(x: np.ndarray, k: int) -> np.ndarray:
    y = np.zeros_like(x) # 1. Keep the "Ruler" size constant
    
    for n in range(-INF, INF + 1):
        target_time = n * k
        
        # 2. Only map if the data fits on the "Ruler"
        if -INF <= target_time <= INF:
            y[INF + n] = x[INF + target_time]
            
    return y

#--- 3.2 USING numpy functions ---
y = np.zeros_like(x)
    n = np.arange(-INF, INF + 1)
    
    # Only keep times 'n' where 'n*k' is inside [-8, 8]
    valid_mask = np.abs(n * k) <= INF
    valid_n = n[valid_mask]
    
    # Map input to output
    y[INF + valid_n] = x[INF + valid_n * k]
    return y

```

---

### **Part 2: Continuous Time (CT) Operations**

**Key Concept:** In continuous time, we don't change the array values usually. Instead, we change the **mathematical function input**.

1. **Shift ():** Subtract  from the time variable.
2. **Scale ():** Multiply the time variable by .
3. **Reverse ():** Negate the time variable.

```python
# --- 1. SETUP: Define a Mathematical Function ---
# Let's define a function x(t)
def x_func(t):
    # A pulse that exists between -1 and 1
    return np.where((t >= -1) & (t <= 1), 1, 0)

# Create a high-resolution time axis
t = np.linspace(-5, 5, 1000)

def plot_ct(t, y, title):
    plt.figure(figsize=(6, 2))
    plt.plot(t, y)
    plt.title(title)
    plt.grid(True)
    plt.show()

plot_ct(t, x_func(t), "Original Continuous Signal x(t)")


# --- 2. TIME REVERSAL: x(-t) ---
# Simply pass -t into the function
y_reversed = x_func(-t)
plot_ct(t, y_reversed, "Time Reversal x(-t)")


# --- 3. TIME SHIFT: x(t - t0) ---
# Shift to the right by 2.
# Important: Right shift is (t - 2)
t0 = 2
y_shifted = x_func(t - t0)
plot_ct(t, y_shifted, f"Time Shift x(t - {t0})")


# --- 4. TIME SCALING: x(a * t) ---
# Compress signal by factor of 2
a = 2
y_scaled = x_func(a * t)
plot_ct(t, y_scaled, f"Time Scaling x({a}t)")

```

---

### **Summary of Syntax**

| Operation | Discrete (Array `x`) | Continuous (Function `x(t)`) |
| --- | --- | --- |
| **Reversal** | `x[::-1]` | `x_func(-t)` |
| **Shift (+k)** | `np.roll(x, k)` (then clean edges) | `x_func(t - k)` |
| **Scale (Compression)** | `x[::k]` | `x_func(k * t)` |

### **Common Pitfall to Watch Out For**

In Continuous Time, if you combine operations (like ), the order matters!

* **The Code Way (Easiest):** Just type the math exactly into the function: `y = x_func(2*t - 4)`.
* **The Manual Way:**
1. Shift first: 
2. Then Scale :


---
---
---


Here is the complete code for **both** Discrete Time (matching your assignment's fixed-size array) and Continuous Time (standard mathematical approach).

### **1. Discrete Time (Assignment Style)**

**Type:** Fixed Array Size (Index -8 to 8).
**Logic:** We manipulate **indices**. Scaling "skips" samples (decimation).

```python
import numpy as np

INF = 8  # The range is -8 to 8

# --- 1. Discrete Time Shift: x[n - k] ---
def dt_shift(x: np.ndarray, k: int) -> np.ndarray:
    if k == 0: return x.copy()
    
    # Shift using roll
    shifted = np.roll(x, k)
    
    # Zero out the "wrapped" values
    if k > 0:
        shifted[:k] = 0   # Right shift -> clear start
    else:
        shifted[k:] = 0   # Left shift -> clear end
    return shifted

# --- 2. Discrete Time Scale: x[kn], using loop ---
def dt_scale(x: np.ndarray, k: int) -> np.ndarray:
    y = np.zeros_like(x)  # Maintain fixed size
    
    # Loop through every target time 'n'
    for n in range(-INF, INF + 1):
        src_time = n * k
        
        # Check if the source time is within bounds
        if -INF <= src_time <= INF:
            # Map indices: Index = INF + Time
            y[INF + n] = x[INF + src_time]
            
    return y

#--- 2.2 USING numpy functions ---
y = np.zeros_like(x)
    n = np.arange(-INF, INF + 1)
    
    # Only keep times 'n' where 'n*k' is inside [-8, 8]
    valid_mask = np.abs(n * k) <= INF
    valid_n = n[valid_mask]
    
    # Map input to output
    y[INF + valid_n] = x[INF + valid_n * k]
    return y


# --- 3. Discrete Time Reversal: x[-n] ---
def dt_reverse(x: np.ndarray) -> np.ndarray:
    # Simply flip the array
    return x[::-1]

```

---

### **2. Continuous Time (General Style)**

**Type:** Mathematical Function .
**Logic:** We manipulate the **input time variable** . Scaling "squeezes" the wave (compression).

```python
# --- Define a sample Continuous Signal x(t) ---
def x_continuous(t):
    # Example: A pulse from -1 to 1
    return np.where(np.abs(t) <= 1, 1.0, 0.0)

# --- 1. Continuous Time Shift: x(t - k) ---
def ct_shift(func, t_array, k):
    # Just subtract k from the time axis
    # If we want x(t-2), we evaluate func at (t-2)
    return func(t_array - k)

# --- 2. Continuous Time Scale: x(at) ---
def ct_scale(func, t_array, a):
    # Multiply time axis by 'a'
    # If we want x(2t), we evaluate func at (2*t)
    return func(a * t_array)

# --- 3. Continuous Time Reversal: x(-t) ---
def ct_reverse(func, t_array):
    # Negate the time axis
    return func(-t_array)

```

### **Comparison Table**

| Operation | Discrete (Assignment Code) | Continuous (Function Code) |
| --- | --- | --- |
| **Shift (+k)** | `np.roll` & mask zeros | `func(t - k)` |
| **Scale (*k)** | Skips samples (Data Loss) | Squeezes shape (Perfect) |
| **Reverse** | `x[::-1]` | `func(-t)` |
| **Complexity** | Harder (Need to handle indices) | Easier (Just Math) |