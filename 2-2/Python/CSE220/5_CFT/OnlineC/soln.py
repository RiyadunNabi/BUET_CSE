import numpy as np
import matplotlib.pyplot as plt

# =====================================================
# Abstract Base Class for Continuous-Time Signals
# =====================================================
class ContinuousSignal:
    """
    Abstract base class for all continuous-time signals.
    Every signal must be defined over a time axis t.
    """

    def __init__(self, t):
        self.t = t

    def values(self):
        """
        Returns the signal values evaluated over time axis t.
        Must be implemented by subclasses.
        """
        raise NotImplementedError("Subclasses must implement this method.")

    def plot(self, title="Signal"):
        """
        Plot the signal in the time domain.
        """
        vals = self.values()
        # Handle complex signals for plotting (plot real part or magnitude)
        if np.iscomplexobj(vals):
            plt.figure(figsize=(10, 4))
            plt.plot(self.t, np.real(vals), label='Real')
            plt.plot(self.t, np.imag(vals), label='Imaginary', linestyle='--')
            plt.legend()
        else:
            plt.figure(figsize=(10, 4))
            plt.plot(self.t, vals)
        
        plt.xlabel("Time (t)")
        plt.ylabel("Amplitude")
        plt.title(title)
        plt.grid(True)
        plt.show()


# =====================================================
# Signal Generator Class
# =====================================================
class SignalGenerator(ContinuousSignal):
    """
    Generates various continuous-time signals.
    """

    def sine(self, amplitude, frequency):
        return amplitude * np.sin(2 * np.pi * frequency * self.t)

    def cosine(self, amplitude, frequency):
        return amplitude * np.cos(2 * np.pi * frequency * self.t)

    def square(self, amplitude, frequency):
        return amplitude * np.sign(np.sin(2 * np.pi * frequency * self.t))

    def sawtooth(self, amplitude, frequency):
        ft = frequency * self.t
        return amplitude * (2 * (ft - np.floor(0.5 + ft)))

    def triangle(self, amplitude, frequency):
        return (2 * amplitude / np.pi) * np.arcsin(np.sin(2 * np.pi * frequency * self.t))

    def cubic(self, coefficient):
        return coefficient * (self.t ** 3)

    def parabolic(self, coefficient):
        return coefficient * (self.t ** 2)

    def rectangular(self, width):
        return np.where(np.abs(self.t) <= width / 2, 1.0, 0.0)

    def pulse(self, start, end):
        return np.where((self.t >= start) & (self.t <= end), 1.0, 0.0)


# =====================================================
# Composite Signal Class
# =====================================================
class CompositeSignal(ContinuousSignal):
    """
    Combines multiple signals into a single composite signal.
    """

    def __init__(self, t):
        super().__init__(t)
        self.components = []

    def add_component(self, signal):
        self.components.append(signal)

    def values(self):
        if not self.components:
            return np.zeros_like(self.t)
        return np.sum(self.components, axis=0)


# =====================================================
# Helper Class for Custom Signals (e.g., Modulated)
# =====================================================
class ArraySignal(ContinuousSignal):
    """
    Wrapper to treat a pre-calculated numpy array as a ContinuousSignal object.
    Used for y(t) which is complex and modulated.
    """
    def __init__(self, t, signal_array):
        super().__init__(t)
        self.signal_array = signal_array

    def values(self):
        return self.signal_array


# =====================================================
# Continuous Fourier Transform Analyzer
# =====================================================
class CFTAnalyzer:
    """
    Computes the Continuous Fourier Transform (CFT)
    using numerical integration (np.trapz).
    """

    def __init__(self, signal, t, frequencies):
        self.signal = signal
        self.t = t
        self.frequencies = frequencies

    def compute_cft(self):
        """
        Compute real and imaginary parts of the CFT.
        Handles both Real and Complex input signals.
        """
        x_t = self.signal.values()
        real_part = []
        imag_part = []

        # Pre-compute exp(-j*2*pi*f*t) components to avoid using np.fft
        # Euler's Identity: e^(-jtheta) = cos(theta) - j*sin(theta)
        
        for f in self.frequencies:
            theta = 2 * np.pi * f * self.t
            kernel_cos = np.cos(theta)
            kernel_sin = np.sin(theta)
            
            # If x(t) is complex: x(t) = u + jv
            # Integral [ (u + jv) * (cos - j*sin) ] dt
            # = Integral [ (u*cos + v*sin) + j(v*cos - u*sin) ] dt
            
            if np.iscomplexobj(x_t):
                u = np.real(x_t)
                v = np.imag(x_t)
                
                integrand_real = u * kernel_cos + v * kernel_sin
                integrand_imag = v * kernel_cos - u * kernel_sin
            else:
                # Standard case for real signals
                integrand_real = x_t * kernel_cos
                integrand_imag = -x_t * kernel_sin

            re = np.trapz(integrand_real, self.t)
            im = np.trapz(integrand_imag, self.t)
            
            real_part.append(re)
            imag_part.append(im)

        return np.array(real_part), np.array(imag_part)

    def plot_spectrum(self):
        """
        Plot magnitude spectrum of the signal.
        """
        real, imag = self.compute_cft()
        magnitude = np.sqrt(real**2 + imag**2)
        
        plt.figure(figsize=(10, 4))
        plt.plot(self.frequencies, magnitude)
        plt.xlabel("Frequency (Hz)")
        plt.ylabel("Magnitude |X(f)|")
        plt.title("CFT Magnitude Spectrum")
        plt.grid(True)
        plt.show()

# =====================================================
# Main Execution (Task 1)
# =====================================================
if __name__ == "__main__":
    # Define time axis t in [-5, 5] with 2000 samples
    t = np.linspace(-5, 5, 2000)
    
    # 1. Define x(t) = Square(t) + Triangle(t)
    gen = SignalGenerator(t)
    composite = CompositeSignal(t)
    
    # Assume A=1, f=1 for base components
    composite.add_component(gen.square(1, 1))
    composite.add_component(gen.triangle(1, 1))
    
    x_t_vals = composite.values()
    
    print("Computing CFT of x(t)...")
    # Define frequency axis covering f in [-10, 10] with 1000 samples
    frequencies = np.linspace(-10, 10, 1000)
    cft_x = CFTAnalyzer(composite, t, frequencies)
    x_real, x_imag = cft_x.compute_cft()
    
    # 2. Define y(t) = modified x(t)
    # i. Phase shift (Modulation): exp(j*2*pi*f0*t)
    # ii. Compression: x(at)
    # Order implied by verification formula |Y(f)| = 1/|a| * |X((f-f0)/a)| is:
    # First Compress: x(at)
    # Then Modulate: x(at) * exp(j*2*pi*f0*t)
    
    a = 10
    f0 = 10
    
    # Create the compressed time grid to evaluate x(at)
    t_compressed = a * t 
    
    # Evaluate x(at) using the generator on the compressed time grid
    gen_compressed = SignalGenerator(t_compressed)
    x_at = gen_compressed.square(1, 1) + gen_compressed.triangle(1, 1)
    
    # Evaluate modulation term on the original time grid t
    modulation = np.exp(1j * 2 * np.pi * f0 * t)
    
    # Combine to form y(t)
    y_vals = x_at * modulation
    
    # Wrap y(t) in a ContinuousSignal object (using helper class)
    y_signal = ArraySignal(t, y_vals)
    
    print("Computing CFT of y(t)...")
    cft_y = CFTAnalyzer(y_signal, t, frequencies)
    y_real, y_imag = cft_y.compute_cft()
    
    # Calculate magnitudes and phases
    Y_mag = np.sqrt(y_real**2 + y_imag**2)
    Y_phase = np.arctan2(y_imag, y_real)
    
    # 3. Calculate Target Verification RHS: 1/|a| * X((f-f0)/a)
    # We need X(f) evaluated at frequencies f' = (f - f0) / a
    frequencies_shifted_scaled = (frequencies - f0) / a
    
    # Compute CFT of x(t) at these specific target frequencies
    # This avoids interpolation errors and directly computes the expected value
    cft_x_target = CFTAnalyzer(composite, t, frequencies_shifted_scaled)
    x_target_real, x_target_imag = cft_x_target.compute_cft()
    
    X_target_mag = np.sqrt(x_target_real**2 + x_target_imag**2)
    X_target_phase = np.arctan2(x_target_imag, x_target_real)
    
    RHS_mag = (1 / np.abs(a)) * X_target_mag
    RHS_phase = X_target_phase # Phase should be same
    
    # 4. Numerical Verification Plots
    plt.figure(figsize=(12, 10))
    
    # Magnitude Comparison
    plt.subplot(2, 1, 1)
    plt.plot(frequencies, Y_mag, label='|Y(f)| (Measured)', linewidth=2)
    plt.plot(frequencies, RHS_mag, '--', label='1/|a| * |X((f-f0)/a)| (Theoretical)', color='red')
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude")
    plt.title("Magnitude Verification")
    plt.legend()
    plt.grid(True)
    
    # Phase Comparison
    plt.subplot(2, 1, 2)
    plt.plot(frequencies, Y_phase, label='Angle Y(f)', linewidth=1, alpha=0.7)
    plt.plot(frequencies, RHS_phase, '--', label='Angle X((f-f0)/a)', color='red', linewidth=1, alpha=0.7)
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Phase (Radians)")
    plt.title("Phase Verification")
    plt.legend()
    plt.grid(True)
    
    plt.tight_layout()
    plt.show()

    # 5. Error Analysis (MSE)
    N = len(frequencies)
    
    # MSE Magnitude
    ise_magnitude = (1/N) * np.sum((Y_mag - RHS_mag)**2)
    print(f"ISE Magnitude: {ise_magnitude}")
    
    # MSE Phase
    # Note: Phase wrapping might cause large MSE even if phases are equivalent (e.g., pi vs -pi).
    # We use a simple difference here as requested, but complex error is often better.
    mse_phase = (1/N) * np.sum((Y_phase - RHS_phase)**2)
    print(f"MSE Phase: {mse_phase}")