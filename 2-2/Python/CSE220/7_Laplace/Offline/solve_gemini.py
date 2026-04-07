import numpy as np
import matplotlib.pyplot as plt

class SmartIrrigation:
    def __init__(self, a=0.5, b=1.0, t_max=20, dt=0.01):
        self.a = a
        self.b = b
        self.t_max = t_max
        self.dt = dt
        self.t = np.arange(0, t_max + dt, dt)

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
        integral = np.sum((integrand[:-1] + integrand[1:]) / 2.0) * self.dt
        return integral

    def inverse_laplace(self, s_list, F_s_values):
        delta_W = s_list[1].imag - s_list[0].imag
        h = np.zeros_like(self.t)
        
        for i, t_val in enumerate(self.t):
            term = F_s_values * np.exp(s_list * t_val)
            h[i] = (delta_W / (2 * np.pi)) * np.sum(term).real
        return h

    def H_s(self, s, U_s):
        factor = (self.b / (s + self.a)) * U_s
        return factor

    def steady_state(self, h):
        """Mean of last 5% of signal."""
        idx = max(1, int(0.05 * len(h)))
        return np.mean(h[-idx:])

    def time_constant(self, h):
        """Time to first reach 63.2% of steady-state."""
        h_ss = self.steady_state(h)
        target = 0.632 * h_ss
        
        if h_ss == 0 or (h_ss > 0 and np.max(h) < target):
            return 0.0
            
        for i, val in enumerate(h):
            if (h_ss > 0 and val >= target) or (h_ss < 0 and val <= target):
                return self.t[i]
        return 0.0

    def rise_time(self, h):
        """Time to go from 10% to 90% of steady-state."""
        h_ss = self.steady_state(h)
        if h_ss == 0:
            return 0.0
            
        low_target = 0.10 * h_ss
        high_target = 0.90 * h_ss
        t_low, t_high = None, None
        
        for i, val in enumerate(h):
            if t_low is None and ((h_ss > 0 and val >= low_target) or (h_ss < 0 and val <= low_target)):
                t_low = self.t[i]
            if t_high is None and ((h_ss > 0 and val >= high_target) or (h_ss < 0 and val <= high_target)):
                t_high = self.t[i]
                
        if t_low is not None and t_high is not None:
            return t_high - t_low
        return 0.0

    def settling_time(self, h):
        """Time after which h(t) stays permanently within ±2% of h_ss."""
        h_ss = self.steady_state(h)
        if h_ss == 0:
            return 0.0
            
        upper_bound = h_ss * 1.02
        lower_bound = h_ss * 0.98
        
        for i in range(len(h) - 1, -1, -1):
            if h[i] > upper_bound or h[i] < lower_bound:
                if i + 1 < len(self.t):
                    return self.t[i + 1]
                else:
                    return self.t[-1]
        return 0.0

    def overshoot(self, h):
        """Percentage overshoot: (h_max - h_ss) / h_ss * 100."""
        h_ss = self.steady_state(h)
        if h_ss <= 0:
            return 0.0
            
        max_val = np.max(h)
        if max_val > h_ss:
            return ((max_val - h_ss) / h_ss) * 100.0
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
        h[n+1] = h[n] + dt * (-a*h[n] + b*u[n])
        """
        h = np.zeros_like(self.t)
        for n in range(len(self.t) - 1):
            dhdt = -self.a * h[n] + self.b * u[n]
            h[n + 1] = h[n] + self.dt * dhdt
        return h


# Initialise system
system = SmartIrrigation(a=0.5, b=1.0, t_max=20, dt=0.01)

inputs = {
    "Step Input":        system.u_step(),
    "Ramp Input":        system.u_ramp(),
    "Sinusoidal Input":  system.u_sin(),
    "Exponential Input": system.u_exponential(),
    "Pulse Input":       system.u_pulse(),
}

# # Bromwich contour parameters setup
# c = 1.0 
# W = 100.0
# N = 5000
# delta_w = 2 * W / N
# omega = -W + np.arange(N) * delta_w
# s_list = c + 1j * omega

# Bromwich contour parameters setup
c = 0.25  
W = 100.0
N = 2000  
delta_w = 2 * W / N
omega = -W + np.arange(N) * delta_w
s_list = c + 1j * omega



colors = ['#2196F3', '#4CAF50', '#FF5722', '#9C27B0', '#FF9800']

for idx, (name, u) in enumerate(inputs.items()):
    print(f"Processing: {name}...")

    # --- Laplace ---
    U_s_vals = np.array([system.laplace_transform(u, s) for s in s_list])
    H_s_vals = system.H_s(s_list, U_s_vals)
    h_laplace = system.inverse_laplace(s_list, H_s_vals)
    
    print(f"\n  ► {name}")
    metrics = system.compute_metrics(h_laplace)
    
    for k, v in metrics.items():
        if isinstance(v, float):
            print(f"      {k.replace('_',' ').title():<22}: {v:.4f}")
        else:
            print(f"      {k.replace('_',' ').title():<22}: {v}")


    # --- Euler ---
    h_euler = system.euler_simulate(u)


    # --- Plot ---
    fig, axes = plt.subplots(1, 2, figsize=(14, 5), sharey=False)
    fig.suptitle(f"Smart Irrigation — {name}", fontsize=13, fontweight='bold')

   # Laplace subplot
    axes[0].plot(system.t, u, 'b--', lw=1.8, label="Input u(t)")
    axes[0].plot(system.t, h_laplace, color=colors[idx], lw=2.2, label="Output h(t)")
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