import numpy as np
import matplotlib.pyplot as plt

# TODO: Define the functions for the different signals
def parabolic_function(x):
    """
    Implement a parabolic function that returns x^2 for -2 <= x <= 2, and 0 elsewhere
    Ref: 
    """
    return np.where((x >= -2) & (x <= 2), x**2, 0)

def triangular_function(x):
    """
    Implement a triangular function that returns 1 - |x|/2 for -2 <= x <= 2, and 0 elsewhere
    Ref: 
    """
    return np.where((x >= -2) & (x <= 2), 1 - np.abs(x)/2, 0)

def sawtooth_function(x):
    """
    Implement a sawtooth function that returns x + 2 for -2 <= x <= 2, and 0 elsewhere
    Ref: 
    """
    return np.where((x >= -2) & (x <= 2), x + 2, 0)

def rectangular_function(x):
    """
    Implement a rectangular (step) function that returns 1 for -2 <= x <= 2, and 0 elsewhere
    Ref: 
    """
    return np.where((x >= -2) & (x <= 2), 1, 0)

# TODO: Implement Fourier Transform using trapezoidal integration
def fourier_transform(signal, frequencies, sampled_times):
    """
    Compute the Fourier Transform of a signal using trapezoidal integration.
    Formula: X(f) = integral( x(t) * e^(-j2πft) dt )
    
    Ref: 
    """
    ft_real = []
    ft_imag = []
    
    # Iterate over each frequency f to compute the integral
    for f in frequencies:
        # Create the complex exponential term: e^(-j * 2 * pi * f * t)
        complex_exponential = np.exp(-1j * 2 * np.pi * f * sampled_times)
        
        # Multiply signal by the complex exponential
        integrand = signal * complex_exponential
        
        # Integrate using trapezoidal rule
        integral = np.trapz(integrand, sampled_times)
        
        ft_real.append(np.real(integral))
        ft_imag.append(np.imag(integral))
        
    return np.array(ft_real), np.array(ft_imag)

# TODO: Implement Inverse Fourier Transform
def inverse_fourier_transform(ft_signal, frequencies, sampled_times):
    """
    Reconstruct the original signal from its Fourier Transform.
    Formula: x(t) = integral( X(f) * e^(j2πft) df )
    
    Ref: [cite: 13, 16]
    """
    real_part, imag_part = ft_signal
    # Reconstruct the complex spectrum X(f)
    X_f = real_part + 1j * imag_part
    
    reconstructed_signal = []
    
    # Iterate over each time t to reconstruct the signal value
    for t in sampled_times:
        # Create the complex exponential term: e^(j * 2 * pi * f * t)
        complex_exponential = np.exp(1j * 2 * np.pi * frequencies * t)
        
        # Multiply spectrum by the complex exponential
        integrand = X_f * complex_exponential
        
        # Integrate over frequency df using trapezoidal rule
        integral = np.trapz(integrand, frequencies)
        
        # The result should be real-valued for real signals
        reconstructed_signal.append(np.real(integral))
        
    return np.array(reconstructed_signal)

# TODO: Implement Inverse Fourier Transform for computing derivatives
def inverse_fourier_transform_for_derivative(ft_signal, frequencies, sampled_times):
    """
    Compute the derivative of a signal using Fourier Transform.
    Property: F{f'(t)} = (j * 2 * pi * f) * F{f(t)}
    
    Ref: [cite: 14, 24, 25]
    """
    real_part, imag_part = ft_signal
    X_f = real_part + 1j * imag_part
    
    # Apply the differentiation property in frequency domain
    # Multiply the spectrum by j * 2 * pi * f
    derivative_spectrum = X_f * (1j * 2 * np.pi * frequencies)
    
    derivative_signal = []
    
    # Perform Inverse Fourier Transform on the modified spectrum
    for t in sampled_times:
        complex_exponential = np.exp(1j * 2 * np.pi * frequencies * t)
        integrand = derivative_spectrum * complex_exponential
        
        # Integrate over frequency
        integral = np.trapz(integrand, frequencies)
        
        derivative_signal.append(np.real(integral))
        
    return np.array(derivative_signal)

# Define sampled times and frequency ranges
sampled_times = np.linspace(-5, 5, 1000)
frequencies_list = [np.linspace(-1, 1, 500), np.linspace(-2, 2, 500), np.linspace(-5, 5, 500)]

functions = {
    "Parabolic Function": parabolic_function,
    "Triangular Function": triangular_function,
    "Sawtooth Function": sawtooth_function,
    "Rectangular Function": rectangular_function,
}

# Plotting for each function
for function_name, func in functions.items():
    y_values = func(sampled_times)
    
    plt.figure(figsize=(10, 6))
    plt.plot(sampled_times, y_values, label=f"Original {function_name}")
    plt.title(f"Original {function_name}")
    plt.xlabel("Time (t)")
    plt.ylabel("Amplitude")
    plt.legend()
    plt.grid()
    plt.show()

    # Fourier Transform and Frequency Spectrum
    for freq_range in frequencies_list:
        ft_signal = fourier_transform(y_values, freq_range, sampled_times)
        reconstructed_signal = inverse_fourier_transform(ft_signal, freq_range, sampled_times)

        plt.figure(figsize=(10, 6))
        plt.plot(freq_range, np.sqrt(ft_signal[0]**2 + ft_signal[1]**2), label="Frequency Spectrum")
        plt.title(f"Frequency Spectrum for {function_name} (Freq Range {freq_range[0]} to {freq_range[-1]})")
        plt.xlabel("Frequency (Hz)")
        plt.ylabel("Magnitude")
        plt.legend()
        plt.grid()
        plt.show()

        # Reconstructed Signal
        plt.figure(figsize=(10, 6))
        plt.plot(sampled_times, y_values, label=f"Original {function_name}", color='blue')
        plt.plot(sampled_times, reconstructed_signal, label=f"Reconstructed {function_name}", color='red', linestyle='--')
        plt.title(f"Reconstructed {function_name} (Freq Range {freq_range[0]} to {freq_range[-1]})")
        plt.xlabel("Time (t)")
        plt.ylabel("Amplitude")
        plt.legend()
        plt.grid()
        plt.show()

        # Derivative using Fourier Transform
        derivative_signal = inverse_fourier_transform_for_derivative(ft_signal, freq_range, sampled_times)
        
        plt.figure(figsize=(10, 6))
        plt.plot(sampled_times, derivative_signal, label=f"Derivative of {function_name}", color='green')
        plt.title(f"Derivative of {function_name} using Fourier Transform (Freq Range {freq_range[0]} to {freq_range[-1]})")
        plt.xlabel("Time (t)")
        plt.ylabel("Amplitude")
        plt.legend()
        plt.grid()
        plt.show()