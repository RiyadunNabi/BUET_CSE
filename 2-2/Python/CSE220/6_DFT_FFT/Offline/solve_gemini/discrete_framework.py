import numpy as np

class DiscreteSignal:
    """
    Represents a discrete-time signal.
    """
    def __init__(self, data):
        # Ensure data is a numpy array, potentially complex
        self.data = np.array(data, dtype=np.complex128)

    def __len__(self):
        return len(self.data)
        
    def pad(self, new_length):
        """
        Zero-pad or truncate signal to new_length.
        Returns a new DiscreteSignal object.
        """
        N = len(self.data)
        if new_length > N:
            padded = np.zeros(new_length, dtype=np.complex128)
            padded[:N] = self.data
            return DiscreteSignal(padded)
        elif new_length < N:
            return DiscreteSignal(self.data[:new_length])
        return DiscreteSignal(self.data.copy())

    def interpolate(self, new_length):
        """
        Resample signal to new_length using linear interpolation.
        Required for Task 1 (Drawing App) to match Power of 2 requirements.
        """
        N = len(self.data)
        if N == 0:
            return DiscreteSignal(np.zeros(new_length, dtype=np.complex128))
        if N == 1:
            return DiscreteSignal(np.ones(new_length, dtype=np.complex128) * self.data[0])
            
        old_indices = np.linspace(0, N - 1, N)
        new_indices = np.linspace(0, N - 1, new_length)
        
        real_part = np.interp(new_indices, old_indices, np.real(self.data))
        imag_part = np.interp(new_indices, old_indices, np.imag(self.data))
        
        return DiscreteSignal(real_part + 1j * imag_part)


class DFTAnalyzer:
    """
    Performs Discrete Fourier Transform using O(N^2) method.
    """
    def compute_dft(self, signal: DiscreteSignal):
        """
        Compute DFT using naive summation O(N^2).
        Returns: numpy array of complex frequency coefficients.
        """
        x = signal.data
        N = len(x)
        if N == 0: return np.array([], dtype=np.complex128)
        
        # Vectorized Naive implementation
        n = np.arange(N)
        k = n.reshape((N, 1))
        e = np.exp(-2j * np.pi * k * n / N)
        X = np.dot(e, x)
        return X

    def compute_idft(self, spectrum):
        """
        Compute Inverse DFT using naive summation O(N^2).
        Returns: numpy array (time-domain samples).
        """
        X = np.array(spectrum, dtype=np.complex128)
        N = len(X)
        if N == 0: return np.array([], dtype=np.complex128)
        
        n = np.arange(N)
        k = n.reshape((N, 1))
        e = np.exp(2j * np.pi * k * n / N)
        x = np.dot(e, X) / N
        return x


class FastFourierTransform(DFTAnalyzer):
    """
    Performs Fast Fourier Transform using Radix-2 DIT Cooley-Tukey Algorithm O(N log N).
    """
    def _fft_radix2(self, x):
        N = len(x)
        if N <= 1:
            return x
        
        even = self._fft_radix2(x[0::2])
        odd = self._fft_radix2(x[1::2])
        
        T = np.array([np.exp(-2j * np.pi * k / N) * odd[k] for k in range(N // 2)])
        
        return np.concatenate([even + T, even - T])

    def compute_dft(self, signal: DiscreteSignal):
        """
        Compute DFT efficiently. Pads signal to nearest power of 2 if necessary.
        """
        x = signal.data
        N = len(x)
        if N == 0: return np.array([], dtype=np.complex128)
        
        # Check if power of 2, if not pad it
        if (N & (N - 1)) != 0:
            next_pow2 = 1 << (N - 1).bit_length()
            x = np.pad(x, (0, next_pow2 - N), 'constant')
            
        return self._fft_radix2(x)

    def compute_idft(self, spectrum):
        """
        Compute IDFT efficiently using the FFT framework:
        x = 1/N * conj(FFT(conj(X)))
        """
        X = np.array(spectrum, dtype=np.complex128)
        N = len(X)
        if N == 0: return np.array([], dtype=np.complex128)
        
        if (N & (N - 1)) != 0:
            next_pow2 = 1 << (N - 1).bit_length()
            X = np.pad(X, (0, next_pow2 - N), 'constant')
            N = len(X)
            
        X_conj = np.conj(X)
        x = np.conj(self._fft_radix2(X_conj)) / N
        return x