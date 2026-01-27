import numpy as np
import matplotlib.pyplot as plt

# from 2205076_first import Signal, LTI_System 
import importlib
first_part = importlib.import_module("2205076_first")

Signal = first_part.Signal
LTI_System = first_part.LTI_System

def run_smoothing_task():
    filename = "input_signal.txt"
    
    try:
        with open(filename, 'r') as f:
            lines = f.readlines()
            
        bounds = lines[0].strip().split()
        n_start = int(bounds[0])
        n_end = int(bounds[1])
        values = [float(v) for v in lines[1].strip().split()]
        
        if len(values) != (n_end - n_start + 1):
            print("Warning: Number of values does not match the index range.")

        # 1.
        INF = max(abs(n_start), abs(n_end)) + 10 
        noisy_signal = Signal(INF)
        
        current_n = n_start
        for val in values:
            noisy_signal.set_value_at_time(current_n, val)
            current_n += 1
            
        # 2.
        noisy_signal.plot("Noisy Input Signal")
        
        # 3.
        h = Signal(INF)
        avg_val = 1.0 / 5.0
        for i in range(-2, 3): # -2, -1, 0, 1, 2
            h.set_value_at_time(i, avg_val)
            
        h.plot("Moving Average Impulse Response")
        
        # 4.
        smoother_system = LTI_System(h)
        
        # 5.
        print("Computing smoothed output...")
        smoothed_output = smoother_system.output(noisy_signal)
        
        # 6.
        smoothed_output.plot("Smoothed Output Signal")
        
    except FileNotFoundError:
        print(f"Error: Could not find '{filename}'.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    run_smoothing_task()