import numpy as np
import matplotlib.pyplot as plt

class Signal:
    def __init__(self, INF):
        self.INF = INF
        self.values = np.zeros(2 * INF + 1)

    def _get_index(self, t):
        return t + self.INF

    def set_value_at_time(self, t, value):
        if -self.INF <= t <= self.INF:
            self.values[self._get_index(t)] = value
    
    def get_value_at_time(self, t):
        if -self.INF <= t <= self.INF:
            return self.values[self._get_index(t)]
        return 0

    def shift(self, k):
        new_signal = Signal(self.INF)
        for n in range(-self.INF, self.INF + 1):
            prev_t = n - k
            val = self.get_value_at_time(prev_t)
            new_signal.set_value_at_time(n, val)
        return new_signal

    def add(self, other):
        new_signal = Signal(self.INF)
        new_signal.values = self.values + other.values
        return new_signal

    def multiply(self, scalar):
        new_signal = Signal(self.INF)
        new_signal.values = self.values * scalar
        return new_signal

    def plot(self, title="Discrete Signal"):
        t_range = np.arange(-self.INF, self.INF + 1)
        plt.figure(figsize=(8, 4))
        plt.stem(t_range, self.values, basefmt=" ")
        plt.title(title)
        plt.xlabel("n")
        plt.ylabel("Amplitude")
        plt.grid(True)
        plt.show()



class LTI_System:
    def __init__(self, impulse_response: Signal):
        self.h = impulse_response

    def linear_combination_of_impulses(self, input_signal: Signal):
        impulses = []
        coefficients = []
        
        for n in range(-input_signal.INF, input_signal.INF + 1):
            val = input_signal.get_value_at_time(n)
            if val != 0:
                coefficients.append(val)
                
                impulse = Signal(input_signal.INF)
                impulse.set_value_at_time(n, 1) 
                impulses.append(impulse)
                
        return impulses, coefficients

    def output(self, input_signal: Signal):
        impulses, coefficients = self.linear_combination_of_impulses(input_signal)
        
        y = Signal(input_signal.INF)
        
        for i in range(len(impulses)):
            coeff = coefficients[i]
            impulse = impulses[i]
            
            k = np.argmax(impulse.values) - impulse.INF
            h_shifted = self.h.shift(k)
            weighted_response = h_shifted.multiply(coeff)
            y = y.add(weighted_response)

        return y

if __name__ == "__main__":
    INF = 10

    # Input signal x(n)
    x = Signal(INF)
    x.set_value_at_time(-2, 1)
    x.set_value_at_time(0, 2)
    x.set_value_at_time(3, -1)

    x.plot("Input Signal x(n)")

    # Impulse response h(n)
    h = Signal(INF)
    h.set_value_at_time(0, 1)
    h.set_value_at_time(1, 0.5)

    h.plot("Impulse Response h(n)")

    # LTI System
    system = LTI_System(h)

    # Output
    y = system.output(x)
    y.plot("Output Signal y(n)")

