import numpy as np
import matplotlib.pyplot as plt

class SmartIrrigation:
    def __init__(self, a=0.5, b=1.0, t_max=20, dt=0.01):
        self.a = a
        self.b = b
        self.t_max = t_max
        self.dt = dt
        self.t = np.arange(0, t_max, dt)

    def u_step(self):
        return np.ones_like(self.t)
        
    def u_ramp(self):
        return 0.1 * self.t
        
    def u_sin(self):
        return np.sin(0.5 * self.t)
        
    def u_exponential(self): 
        return 1 - np.exp(-0.3 * self.t)
        
    def u_pulse(self):
        return np.where(self.t < 5, 1.0, 0.0)

    def laplace_transform(self, f, s):
        integrand = f * np.exp(-s * self.t)
        return np.sum((integrand[:-1] + integrand[1:]) / 2.0) * self.dt

    def inverse_laplace(self, s_list, H_s_values):
        dw = np.imag(s_list[1]) - np.imag(s_list[0]) if len(s_list) > 1 else 0
        h_t = np.zeros_like(self.t, dtype=float)
        H_s_arr = np.array(H_s_values)
        s_arr = np.array(s_list)
        for i, t in enumerate(self.t):
            term = H_s_arr * np.exp(s_arr * t)
            h_t[i] = (dw / (2 * np.pi)) * np.sum(np.real(term))
        return h_t

    def H_s(self, s, U_s):
        return (self.b / (s + self.a)) * U_s

    def steady_state(self, h):
        """Mean of last 5% of signal."""
        idx = int(1 + 0.05 * len(h))
        return np.mean(h[-idx:])

    def time_constant(self, h):
        """Time to first reach 63.2% of steady-state."""
        h_ss = self.steady_state(h)
        target = 0.632 * h_ss
        if h_ss > 1e-4:
            idx = np.argmax(h >= target)
            return self.t[idx]
        return 0.0

    def rise_time(self, h):
        """Time to go from 10% to 90% of steady-state."""
        h_ss = self.steady_state(h)
        if h_ss > 1e-4:
            low = 0.1 * h_ss
            high = 0.9 * h_ss
            idx_low = np.argmax(h >= low)
            idx_high = np.argmax(h >= high)
            return self.t[idx_high] - self.t[idx_low]
        return 0.0

    def settling_time(self, h):
        """Time after which h(t) stays permanently within ±2% of h_ss."""
        h_ss = self.steady_state(h)
        if abs(h_ss) < 1e-4: return 0.0
        lower_bound = 0.98 * h_ss
        upper_bound = 1.02 * h_ss
        outside = (h < lower_bound) | (h > upper_bound)
        if np.any(outside):
            last_outside_idx = np.where(outside)[0][-1]
            if last_outside_idx + 1 < len(self.t):
                return self.t[last_outside_idx + 1]
            else:
                return self.t[-1]
        return 0.0

    def overshoot(self, h):
        """Percentage overshoot: (h_max - h_ss) / h_ss * 100."""
        h_ss = self.steady_state(h)
        if h_ss > 1e-4:
            h_max = np.max(h)
            if h_max > h_ss:
                return (h_max - h_ss) / h_ss * 100.0
        return 0.0

    def compute_metrics(self, h):
        return {
            "steady_state":  self.steady_state(h),
            "time_constant": self.time_constant(h),
            "rise_time":     self.rise_time(h),
            "settling_time": self.settling_time(h),
            "overshoot_%":   self.overshoot(h),
        }

    def euler_simulate(self, u):
        """
        Euler method for dh/dt = -a*h(t) + b*u(t)
        """
        h = np.zeros_like(self.t)
        for n in range(len(self.t) - 1):
            dhdt = -self.a * h[n] + self.b * u[n]
            h[n + 1] = h[n] + self.dt * dhdt
        return h

def run_simulation(system, inputs, title_prefix="Smart Irrigation"):
    # Bromwich contour parameters
    c = 0.2  # positive value, large enough to converge but small enough to avoid numerical instability
    W = 100  # determines highest frequency
    N = 5000 # frequency resolution
    
    dw = 2 * W / N
    w_k = -W + np.arange(N) * dw
    s_list = c + 1j * w_k
    colors = ['#2196F3', '#4CAF50', '#FF5722', '#9C27B0', '#FF9800']
    
    for idx, (name, u) in enumerate(inputs.items()):
        print(f"Processing: {name}...")
        
        # --- Laplace ---
        U_s_vals = [system.laplace_transform(u, s) for s in s_list]
        H_s_vals = [system.H_s(s, U_s) for s, U_s in zip(s_list, U_s_vals)]
        h_laplace = system.inverse_laplace(s_list, H_s_vals)

        print(f"\n  ► {name}")
        metrics = system.compute_metrics(h_laplace)
        for k, v in metrics.items():
            print(f"      {k.replace('_',' ').title():<22}: {v:.4f}")

        # --- Euler ---
        h_euler = system.euler_simulate(u)

        # --- Plot ---
        fig, axes = plt.subplots(1, 2, figsize=(14, 5), sharey=False)
        fig.suptitle(f"{title_prefix} — {name} [a={system.a}, b={system.b}]", fontsize=13, fontweight='bold')

        # Laplace subplot
        axes[0].plot(system.t, u, 'b--', lw=1.8, label="Input u(t)")
        axes[0].plot(system.t, h_laplace, color=colors[idx % len(colors)], lw=2.2, label="Output h(t)")
        axes[0].set_title("Laplace Transform Simulation", fontweight='bold')
        axes[0].set_xlabel("Time (s)", fontsize=11)
        axes[0].set_ylabel("Water Level / Input", fontsize=11)
        axes[0].legend(fontsize=10)
        axes[0].grid(True, alpha=0.3)

        # Euler subplot
        axes[1].plot(system.t, u, 'b--', lw=1.8, label="Input u(t)")
        axes[1].plot(system.t, h_euler, color='tomato', lw=2.2, label="Output h(t)")
        axes[1].set_title("Euler Method Simulation", fontweight='bold')
        axes[1].set_xlabel("Time (s)", fontsize=11)
        axes[1].set_ylabel("Water Level / Input", fontsize=11)
        axes[1].legend(fontsize=10)
        axes[1].grid(True, alpha=0.3)

        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    print("========================================")
    print("Part 1: Base System Simulation")
    print("========================================")
    system = SmartIrrigation(a=0.5, b=1.0, t_max=20, dt=0.01)
    inputs = {
        "Step Input":        system.u_step(),
        "Ramp Input":        system.u_ramp(),
        "Sinusoidal Input":  system.u_sin(),
        "Exponential Input": system.u_exponential(),
        "Pulse Input":       system.u_pulse(),
    }
    run_simulation(system, inputs, "Standard Run")
    
    print("\n========================================")
    print("Part 2: Parameter Variation (a, b configs)")
    print("========================================")
    configs = [
        {"a": 0.2, "b": 1.0, "desc": "Config A: Low Outflow (a=0.2). Expect higher steady state and slower decay."},
        {"a": 1.0, "b": 1.0, "desc": "Config B: Fast Outflow (a=1.0). Expect lower steady state and faster decay."},
        {"a": 0.5, "b": 2.0, "desc": "Config C: High Gain (b=2.0). Expect proportional increase in output levels."}
    ]
    
    for cfg in configs:
        print(f"\nEvaluating {cfg['desc']}")
        sys_var = SmartIrrigation(a=cfg['a'], b=cfg['b'], t_max=20, dt=0.01)
        # Using step input for variations as it cleanly shows steady-state and time constant changes
        sys_inputs = {"Step Input": sys_var.u_step()}
        run_simulation(sys_var, sys_inputs, "Param Variation")
