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
        # plt.figure(figsize=(10, 4))
        plt.plot(self.t, self.values())
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
    Each method returns a numpy array of signal samples.
    """

    def sine(self, amplitude, frequency):
        """Generate a sine wave."""
        return amplitude * np.sin(2*np.pi*frequency*self.t)

    def cosine(self, amplitude, frequency):
        """Generate a cosine wave."""
        return amplitude * np.cos(2*np.pi*frequency*self.t)

    def square(self, amplitude, frequency):
        """Generate a square wave using sign of sine."""
        return amplitude * np.sign(np.sin(2 * np.pi * frequency * self.t))

    def sawtooth(self, amplitude, frequency):
        """Generate a sawtooth wave."""
        ft = frequency * self.t
        return amplitude * (2 * (ft - np.floor(0.5 + ft)))

    def triangle(self, amplitude, frequency):
        """Generate a triangle wave."""
        return (2*amplitude/np.pi)*np.arcsin(np.sin(2*np.pi*frequency*self.t))

    def cubic(self, coefficient):
        """Generate a cubic polynomial signal."""
        return coefficient * (self.t ** 3)

    def parabolic(self, coefficient):
        """Generate a parabolic signal."""
        return coefficient * (self.t**2)

    def rectangular(self, width):
        """Generate a rectangular window centered at t=0."""
        return np.where(np.abs(self.t) <= width / 2, 1.0, 0.0)

    def pulse(self, start, end):
        """Generate a finite pulse active between start and end."""
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
        """
        Add a signal component to the composite signal.
        """
        self.components.append(signal)

    def values(self):
        """
        Sum all signal components.
        """
        if not self.components:
            return np.zeros_like(self.t)
        totalSignal= np.sum(self.components, axis=0)
        return totalSignal


# =====================================================
# Continuous Fourier Transform Analyzer
# =====================================================
class CFTAnalyzer:
    """
    Computes the Continuous Fourier Transform (CFT)
    using numerical integration (np.trapz). Returns: (real_part, imag_part) as numpy arrays.
    """

    def __init__(self, signal, t, frequencies):
        self.signal = signal
        self.t = t
        self.frequencies = frequencies

    def compute_cft(self):
        """
        Compute real and imaginary parts of the CFT.
        """
        x_t = self.signal.values()
        real_part = []
        imag_part = []
        
        for f in self.frequencies: #e^(-jwt) = cos(wt) -jsin(wt)
            re = np.trapz(x_t*np.cos(2*np.pi*f*self.t), self.t)
            im = -np.trapz(x_t*np.sin(2*np.pi*f*self.t), self.t)
            real_part.append(re)
            imag_part.append(im)

        return np.array(real_part), np.array(imag_part)

    def plot_spectrum(self):
        """
        Plot magnitude spectrum of the signal.
        """
        real, imag = self.compute_cft()
        magnitude = np.sqrt(real**2 + imag**2)
        
        # plt.figure(figsize=(10, 4))
        plt.plot(self.frequencies, magnitude)
        plt.xlabel("Frequency (Hz)")
        plt.ylabel("Magnitude |X(f)|")
        plt.title("CFT Magnitude Spectrum")
        plt.grid(True)
        plt.show()


# =====================================================
# Inverse Continuous Fourier Transform
# =====================================================
class InverseCFT:
    """
    Reconstructs time-domain signal using ICFT.
    """

    def __init__(self, spectrum, frequencies, t):
        self.spectrum = spectrum #real, img
        self.frequencies = frequencies
        self.t = t

    def reconstruct(self):
        """
        Perform inverse CFT using numerical integration.
        """
        X_real, X_imag = self.spectrum
        x_reconstructed = []

        for t_val in self.t:
            cos_wt = np.cos(2 * np.pi * self.frequencies * t_val)
            sin_wt = np.sin(2 * np.pi * self.frequencies * t_val)
            
            integrand = (X_real * cos_wt) - (X_imag * sin_wt)
            
            val = np.trapz(integrand, self.frequencies)
            x_reconstructed.append(val)

        return np.array(x_reconstructed)


# =====================================================
# Main Execution (Task 1)
# =====================================================
if __name__ == "__main__":
    t = np.linspace(-1, 1, 1000)
    gen = SignalGenerator(t)
    sinA = gen.sine(1,7)
    sinB = gen.sine(1,1)

    composite = CompositeSignal(t)
    composite.add_component(2*sinA)
    composite.add_component(- sinB * 4*sinB * sinA)
    composite.add_component(sinB)
    composite.plot("Composite Signal")

    frequencies = np.linspace(-15, 15, 1000)
    cft = CFTAnalyzer(composite, t, frequencies)
    cft.plot_spectrum()

    icft = InverseCFT(cft.compute_cft(), frequencies, t)
    x_rec = icft.reconstruct()

    plt.plot(t, composite.values(), label="Original")
    plt.plot(t, x_rec, '--', label="Reconstructed")
    plt.legend()
    plt.title("Reconstruction using ICFT")
    plt.show()
