import numpy as np


class DiscreteSignal:
    """
    Represents a discrete-time signal.
    """
    def __init__(self, data):
        self.data = np.array(data, dtype=np.complex128)

    def __len__(self):
        return len(self.data)

    def pad(self, new_length):
        """
        Zero-pad or truncate signal to new_length.
        Returns a new DiscreteSignal object.
        """
        current_length = len(self.data)
        if new_length >= current_length:
            padded = np.zeros(new_length, dtype=np.complex128)
            padded[:current_length] = self.data
        else:
            padded = self.data[:new_length]
        return DiscreteSignal(padded)

    def interpolate(self, new_length):
        """
        Resample signal to new_length using linear interpolation.
        Required for Task 3 FFT (Drawing App) when N is not a power of 2.
        """
        current_length = len(self.data)
        if current_length == new_length:
            return DiscreteSignal(self.data.copy())

        old_indices = np.linspace(0, current_length - 1, current_length)
        new_indices = np.linspace(0, current_length - 1, new_length)

        real_interp = np.interp(new_indices, old_indices, self.data.real)
        imag_interp = np.interp(new_indices, old_indices, self.data.imag)

        return DiscreteSignal(real_interp + 1j * imag_interp)


class DFTAnalyzer:
    """
    Performs Discrete Fourier Transform using O(N^2) naive summation.
    """

    def compute_dft(self, signal: DiscreteSignal):
        """
        Compute DFT using naive summation.
        X[k] = sum_{n=0}^{N-1} x[n] * e^{-j*2*pi*k*n/N}
        Returns: numpy array of complex frequency coefficients.
        """
        x = signal.data
        N = len(x)
        X = np.zeros(N, dtype=np.complex128)
        for k in range(N):
            for n in range(N):
                X[k] += x[n] * np.exp(-1j * 2 * np.pi * k * n / N)
        return X

    def compute_idft(self, spectrum):
        """
        Compute Inverse DFT using naive summation.
        x[n] = (1/N) * sum_{k=0}^{N-1} X[k] * e^{j*2*pi*k*n/N}
        Returns: numpy array (time-domain samples).
        """
        X = np.array(spectrum, dtype=np.complex128)
        N = len(X)
        x = np.zeros(N, dtype=np.complex128)
        for n in range(N):
            for k in range(N):
                x[n] += X[k] * np.exp(1j * 2 * np.pi * k * n / N)
            x[n] /= N
        return x


class FastFourierTransform(DFTAnalyzer):
    """
    Implements Radix-2 Decimation-in-Time (DIT) Cooley-Tukey FFT algorithm.
    Inherits from DFTAnalyzer and overrides compute_dft / compute_idft.
    Falls back to naive DFT for non-power-of-2 sizes (or use padding externally).
    """

    def _is_power_of_two(self, n):
        return n > 0 and (n & (n - 1)) == 0

    def _fft_recursive(self, x):
        N = len(x)
        if N <= 1:
            return x
        if not self._is_power_of_two(N):
            # Fall back to naive DFT for non-power-of-2
            sig = DiscreteSignal(x)
            return super().compute_dft(sig)

        # Split even/odd
        even = self._fft_recursive(x[0::2])
        odd = self._fft_recursive(x[1::2])

        # Twiddle factors
        T = np.exp(-1j * 2 * np.pi * np.arange(N // 2) / N) * odd

        return np.concatenate([even + T, even - T])

    def _ifft_recursive(self, X):
        N = len(X)
        # IFFT via conjugate trick: IFFT(X) = conj(FFT(conj(X))) / N
        x = np.conj(self._fft_recursive(np.conj(X))) / N
        return x

    def compute_dft(self, signal: DiscreteSignal):
        """
        Compute FFT (Radix-2 DIT Cooley-Tukey).
        If N is not a power of 2, pads to next power of 2 then truncates.
        """
        x = signal.data.copy()
        N = len(x)
        if not self._is_power_of_two(N):
            # Zero-pad to next power of 2
            next_pow2 = 1
            while next_pow2 < N:
                next_pow2 <<= 1
            padded_signal = signal.pad(next_pow2)
            result = self._fft_recursive(padded_signal.data)
            # Return only first N coefficients (approximation)
            return result[:N]
        return self._fft_recursive(x)

    def compute_idft(self, spectrum):
        """
        Compute Inverse FFT using conjugate trick.
        """
        X = np.array(spectrum, dtype=np.complex128)
        N = len(X)
        if not self._is_power_of_two(N):
            # Zero-pad to next power of 2
            next_pow2 = 1
            while next_pow2 < N:
                next_pow2 <<= 1
            padded = np.zeros(next_pow2, dtype=np.complex128)
            padded[:N] = X
            result = self._ifft_recursive(padded)
            return result[:N]
        return self._ifft_recursive(X)

        