import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# ==========================================
# Import your existing Framework
# ==========================================
# Assuming 'task1_signal_framework.py' is in the same folder or parent folder
try:
    import task1_signal_framework as framework
except ImportError:
    # Fallback: If not found, we assume the user is running this where the file is
    sys.path.append(os.path.join(os.path.dirname(__file__), '..','..', 'Offline on CFT'))
    try:
        import task1_signal_framework as framework
    except ImportError:
        print("Error: 'task1_signal_framework.py' not found. Please place it in the same folder.")
        sys.exit(1)

# ==========================================
# 1. Implement the Piecewise Function
# ==========================================

# Left Side (-3 to -1):        • Formula: y = (t + 3)^2
# Middle (-1 to 1):            • Formula: y = 5 — t^2   (assuming)
# Right Side (1 to 3):         • Formula: y = (t — 3)^2
class PiecewiseSignal(framework.ContinuousSignal):
    def values(self):
        # Initialize output array with zeros
        y = np.zeros_like(self.t)
        
        # Section 1: -3 to -1 (Parabola rising)
        # Equation: (t + 3)^2
        mask1 = (self.t >= -3) & (self.t < -1)
        y[mask1] = (self.t[mask1] + 3)**2
        
        # Section 2: -1 to 1 (Parabola cap)
        # Equation: 5 - t^2
        mask2 = (self.t >= -1) & (self.t <= 1)
        y[mask2] = 5 - self.t[mask2]**2
        
        # Section 3: 1 to 3 (Parabola falling)
        # Equation: (t - 3)^2
        mask3 = (self.t > 1) & (self.t <= 3)
        y[mask3] = (self.t[mask3] - 3)**2
        
        return y

# ==========================================
# Main Execution
# ==========================================
if __name__ == "__main__":
    # 1. Setup Time and Signal
    # We use a finer resolution to make the integration (trapezoid) accurate
    t = np.linspace(-5, 5, 1000)
    signal = PiecewiseSignal(t)
    
    # 2. Plot the Input Signal (Visual Verification)
    plt.figure(figsize=(12, 4))
    plt.subplot(1, 2, 1)    #plt.subplot(rows, columns, index)
    plt.plot(t, signal.values(), label='x(t)')  #x(t) vs t
    plt.title("Input Piecewise Function")
    plt.grid(True)
    plt.legend() #Since you used label='x(t)', this displays the label on the plot. If you don’t call legend(), the label won’t show.

    # 3. Compute Fourier Transform (FT)
    # Range should be wide enough to capture the energy
    freqs = np.linspace(-5, 5, 1000)
    analyzer = framework.CFTAnalyzer(signal, t, freqs)
    
    real_part, imag_part = analyzer.compute_cft()
    
    # Calculate Magnitude |X(f)|
    magnitude = np.sqrt(real_part**2 + imag_part**2)

    # Plot Spectrum
    plt.subplot(1, 2, 2)
    plt.plot(freqs, magnitude, color='orange', label='|X(f)|')
    plt.title("Frequency Spectrum (Magnitude)")
    plt.xlabel("Frequency (Hz)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

    # ==========================================
    # 4. Prove Parseval's Theorem
    # ==========================================
    print("="*40)
    print("Parseval's Theorem Verification")
    print("="*40)

    # Calculate LHS: Energy in Time Domain
    # Integral |x(t)|^2 dt
    energy_time = np.trapezoid(np.abs(signal.values())**2, t)
    
    # Calculate RHS: Energy in Frequency Domain
    # Integral |X(f)|^2 df
    # Note: Since we use df (Hz), the factor is 1. If we used dw, it would be 1/2pi.
    energy_freq = np.trapezoid(magnitude**2, freqs)

    print(f"LHS (Time Domain Energy)      : {energy_time:.4f} Joules")
    print(f"RHS (Frequency Domain Energy) : {energy_freq:.4f} Joules")
    
    error = abs(energy_time - energy_freq)
    print(f"Difference (Error)            : {error:.4f}")
    
    if error < 0.5: # Allow small error due to numerical integration (trapezoid)
        print("\n>> RESULT: Parseval's Theorem PROVEN! (Energies match)")
    else:
        print("\n>> RESULT: High error. Try increasing resolution of 't' or 'freqs'.")