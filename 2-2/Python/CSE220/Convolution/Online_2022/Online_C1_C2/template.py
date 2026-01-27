import numpy as np
import matplotlib.pyplot as plt

# Todo: Define Signal class
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

class SuperSignal:
    def __init__(self):
        self.components = []

    def add(self, signal: Signal, coefficient=1.0):
        self.components.append((coefficient, signal))


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

    def output_super(self, supersignal: SuperSignal):
        """
        Calculates the output for a superposition of signals.
        y_super[n] = Sum( coefficient_i * System(x_i[n]) )
        """
        # Initialize an accumulator signal with zeros (using the system's INF)
        y_total = Signal(self.h.INF)
        
        # Iterate through every component (coefficient, signal) in the SuperSignal
        for coeff, component_signal in supersignal.components:
            # 1. Get the system output for the individual component signal
            component_output = self.output(component_signal)
            
            # 2. Scale the output by the coefficient (Scalar Multiplication)
            weighted_output = component_output.multiply(coeff)
            
            # 3. Add to the total result (Additivity)
            y_total = y_total.add(weighted_output)
            
        return y_total
##############################################################
        
        
# Todo: Define LTI class

# if __name__ == "__main__":
#     INF = 10

#     # Component signals
#     x1 = Signal(INF)
#     x1.set_value_at_time(0, 1)

#     x2 = Signal(INF)
#     x2.set_value_at_time(2, 1)

#     # Todo: Create SuperSignal: x(n) = 2*x1(n) - x2(n)

#     # Impulse response
#     h = Signal(INF)
#     h.set_value_at_time(0, 1)
#     h.set_value_at_time(1, 0.5)

#     system = LTI_System(h)

#     # Todo: Output using superposition

# --- Main Execution ---
if __name__ == "__main__":
    INF = 10

    # 1. Define Component signals
    x1 = Signal(INF)
    x1.set_value_at_time(0, 1) # Impulse at n=0

    x2 = Signal(INF)
    x2.set_value_at_time(2, 1) # Impulse at n=2

    # 2. Create SuperSignal: x(n) = 2*x1(n) - x2(n)
    s_sig = SuperSignal()
    s_sig.add(x1, 2.0)   # Add x1 with weight 2
    s_sig.add(x2, -1.0)  # Add x2 with weight -1

    # 3. Define Impulse response h[n]
    h = Signal(INF)
    h.set_value_at_time(0, 1)
    h.set_value_at_time(1, 0.5)
    # h = {1, 0.5} starting at n=0

    # 4. Initialize System
    system = LTI_System(h)

    # 5. Calculate Output using superposition
    y_super = system.output_super(s_sig)
    
    # 6. Display Result
    # Expected logic: 
    # Output for x1 (delta[n]) -> h[n] -> {1, 0.5} at 0,1
    # Output for x2 (delta[n-2]) -> h[n-2] -> {1, 0.5} at 2,3
    # Superposition: 2*{1, 0.5} - 1*{shifted}
    # = {2, 1} at 0,1  MINUS  {1, 0.5} at 2,3
    # Result should be: n=0: 2, n=1: 1, n=2: -1, n=3: -0.5
    
    print("Output Values (Non-zero):")
    for n in range(-INF, INF + 1):
        val = y_super.get_value_at_time(n)
        if val != 0:
            print(f"n={n}: {val}")
            
    y_super.plot("Output of Superposition")