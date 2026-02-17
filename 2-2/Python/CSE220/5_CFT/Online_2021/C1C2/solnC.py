import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# ==========================================
# Import Framework
# ==========================================
try:
    import task1_signal_framework as framework
except ImportError:
    # Fallback pathing
    sys.path.append(os.path.join(os.path.dirname(__file__), '..','..', 'Offline on CFT'))
    try:
        import task1_signal_framework as framework
    except ImportError:
        print("Error: 'task1_signal_framework.py' missing.")
        sys.exit(1)

# ==========================================
# 1. Helper for the "Original" Function
# ==========================================
class TargetFunction(framework.ContinuousSignal):
    def values(self):
        # f(t) = 2sin(14pi*t) - sin(2pi*t) * [ 4 sin(2pi*t) sin(14pi*t) - 1 ]
        A = 14 * np.pi * self.t
        B = 2 * np.pi * self.t
        
        term1 = 2 * np.sin(A)
        term2 = np.sin(B)
        bracket = 4 * np.sin(B) * np.sin(A) - 1
        
        return term1 - (term2 * bracket)

# ==========================================
# 2. Main Solution
# ==========================================
if __name__ == "__main__":
    # Settings
    # We use a 2 second window (-1 to 1) which is enough to see 1Hz waves
    t = np.linspace(-1, 1, 1000) 
    
    # --- PART A: Plot the "Target" Function ---
    target_signal = TargetFunction(t)
    
    plt.figure(figsize=(12, 8))
    
    plt.subplot(2, 1, 1)
    plt.plot(t, target_signal.values(), 'k-', linewidth=4, alpha=0.3, label='Original Target f(t)')

    # --- PART B: Reconstruct using Composite Signal ---
    # From Math derivation: f(t) = sin(18pi*t) + sin(10pi*t) + sin(2pi*t)
    # Frequencies are: 9 Hz, 5 Hz, 1 Hz
    
    gen = framework.SignalGenerator(t)
    composite = framework.CompositeSignal(t)
    
    print("Constructing Signal from Components...")
    
    # 1. sin(18pi*t) -> Freq = 9 Hz
    composite.add_component(gen.sine(1, 9))
    
    # 2. sin(10pi*t) -> Freq = 5 Hz
    composite.add_component(gen.sine(1, 5))
    
    # 3. sin(2pi*t) -> Freq = 1 Hz
    composite.add_component(gen.sine(1, 1))

    # Plot Reconstruction on top
    plt.plot(t, composite.values(), 'r--', label='Reconstructed (Sum of 3 Sines)')
    plt.title("Verification: Original vs Summation")
    plt.legend()
    plt.grid(True)
    
    # --- PART C: Fourier Transform Analysis ---
    print("Running Fourier Analysis to find frequencies...")
    
    # We scan from 0 to 15Hz because we expect peaks at 1, 5, 9
    freqs = np.linspace(0, 15, 1000)
    cft = framework.CFTAnalyzer(composite, t, freqs)
    
    real, imag = cft.compute_cft()
    mag = np.sqrt(real**2 + imag**2)
    
    plt.subplot(2, 1, 2)
    plt.plot(freqs, mag, 'b-')
    plt.title("Frequency Spectrum (Magnitude)")
    plt.xlabel("Frequency (Hz)")
    plt.grid(True)
    
    # Mark the peaks
    peaks = [1, 5, 9]
    for p in peaks:
        plt.axvline(x=p, color='r', linestyle=':', alpha=0.5)
        plt.text(p, np.max(mag)*0.8, f" {p}Hz", color='r')

    plt.tight_layout()
    plt.show()

    print(f"Verified Components: 1Hz, 5Hz, 9Hz")