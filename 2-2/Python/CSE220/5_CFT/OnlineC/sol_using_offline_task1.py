import sys
import os
import numpy as np
import matplotlib.pyplot as plt

# =================================================================
# 1. SETUP IMPORT PATH
# =================================================================
# We need to import 'task1_signal_framework.py' from the sibling directory 'Offline on CFT'
# Structure:
#   Parent_Dir/
#       |-- Offline on CFT/
#       |       |-- task1_signal_framework.py
#       |-- OnlineC/
#               |-- solnusingprev.py  <-- (This file)

current_dir = os.path.dirname(os.path.abspath(__file__))
target_dir = os.path.join(current_dir, '..', 'Offline on CFT')
sys.path.append(target_dir)

try:
    import task1_signal_framework as framework
except ImportError:
    print("Error: Could not import 'task1_signal_framework'.")
    print(f"Make sure the file exists in: {os.path.abspath(target_dir)}")
    sys.exit(1)

# =================================================================
# 2. HELPER CLASS
# =================================================================
class ProcessedSignal(framework.ContinuousSignal):
    """
    A wrapper to treat a pre-calculated numpy array (e.g., y(t)) 
    as a ContinuousSignal object compatible with the framework.
    """
    def __init__(self, t, values_array):
        super().__init__(t)
        self._values = values_array

    def values(self):
        return self._values

# =================================================================
# 3. MAIN SOLUTION
# =================================================================
if __name__ == "__main__":
    # --- Configuration ---
    t = np.linspace(-5,5,2000)
    
    f0 = 10
    a = 10
    
    # --- Step 1: Define x(t) = Square(t) + Triangle(t) ---
    print("Generating x(t)...")
    gen = framework.SignalGenerator(t)
    x_signal = framework.CompositeSignal(t)
    
    # Assuming amplitude=1, frequency=1 for the base shapes
    x_signal.add_component(gen.square(1, 1))
    x_signal.add_component(gen.triangle(1, 1))
    
    # --- Step 2: Define y(t) = Modified x(t) ---
    # Operations:
    # i.  Phase shift (Modulation) by 2*pi*f0*t
    # ii. Compression by a=10
    # To match the verification target |X((f-f0)/a)|, the order must be:
    # y(t) = x(at) * e^(j*2*pi*f0*t)
    
    print("Calculating y(t)...")
    
    # 1. Calculate x(at)
    # We create a temporary generator on the compressed time axis (a*t)
    t_compressed = a * t
    gen_compressed = framework.SignalGenerator(t_compressed)
    
    # Recreate the signal structure on the compressed time
    vals_compressed = gen_compressed.square(1, 1) + gen_compressed.triangle(1, 1)
    
    # 2. Calculate Modulation e^(j*2*pi*f0*t)
    modulation = np.exp(1j * 2 * np.pi * f0 * t)   # Now y_vals is COMPLEX!
    # The Crash: inside your analyzer:re = np.trapz(x_t * cos...)Since x_t is complex, the result re becomes Complex (e.g., $3 + 4j$).Later, you try np.arctan2(complex, complex), and Python screams because arctan2 only accepts plain numbers (floats).

    # 3. Combine
    y_vals = vals_compressed * modulation
    
    # Wrap y(t) so we can pass it to the CFTAnalyzer
    y_signal = ProcessedSignal(t, y_vals)

    # --- Step 3: Compute CFTs ---
    print("Computing CFTs...")
    freqs = np.linspace(-10, 10, 1000)
    
    # CFT of Y(f)
    analyzer_y = framework.CFTAnalyzer(y_signal, t, freqs)
    y_real, y_imag = analyzer_y.compute_cft()
    Y_spectrum=y_real + 1j * y_imag
    Y_mag=np.abs(Y_spectrum) # Y_mag = np.sqrt(y_real**2 + y_imag**2) 
    # Y_phase = np.arctan2(y_imag, y_real) #wrong
    Y_phase = np.angle(Y_spectrum) # This replaces arctan2 safely

    # --- Step 4: Compute Verification RHS ---
    # Target: (1/|a|) * X((f - f0) / a)
    # Instead of computing X(f) and interpolating, we compute X directly 
    # at the shifted/scaled frequencies for maximum accuracy.
    
    freqs_target = (freqs - f0) / a
    
    # CFT of X(t) evaluated at freqs_target
    analyzer_x_target = framework.CFTAnalyzer(x_signal, t, freqs_target)
    x_target_real, x_target_imag = analyzer_x_target.compute_cft()
    
    X_target_mag = np.sqrt(x_target_real**2 + x_target_imag**2)
    X_target_phase = np.arctan2(x_target_imag, x_target_real)
    
    # Apply amplitude scaling 1/|a|
    RHS_mag = (1 / np.abs(a)) * X_target_mag
    RHS_phase = X_target_phase

    # --- Step 5: Visualization ---
    plt.figure(figsize=(12, 10))

    # Plot 1: Magnitude Comparison
    plt.subplot(2, 1, 1)
    plt.plot(freqs, Y_mag, 'b-', label='|Y(f)| (Calculated)', linewidth=2)
    plt.plot(freqs, RHS_mag, 'r--', label=r'$\frac{1}{|a|} |X(\frac{f-f_0}{a})|$ (Theory)', linewidth=2)
    plt.title('Magnitude Verification')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Magnitude')
    plt.legend()
    plt.grid(True)

    # Plot 2: Phase Comparison
    plt.subplot(2, 1, 2)
    plt.plot(freqs, Y_phase, 'b-', label='Angle Y(f)', linewidth=1.5, alpha=0.7)
    plt.plot(freqs, RHS_phase, 'r--', label=r'Angle $X(\frac{f-f_0}{a})$', linewidth=1.5, alpha=0.7)
    plt.title('Phase Verification')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Phase (rad)')
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

    # --- Step 6: Error Analysis ---
    mse_mag = np.mean((Y_mag - RHS_mag)**2)
    mse_phase = np.mean((Y_phase - RHS_phase)**2)
    
    print("-" * 30)
    print("Error Analysis:")
    print(f"ISE Magnitude : {mse_mag:.6e}")
    print(f"MSE Phase     : {mse_phase:.6e}")
    print("-" * 30)