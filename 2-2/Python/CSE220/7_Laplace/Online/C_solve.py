import numpy as np
import matplotlib.pyplot as plt

class SmartIrrigation:
    def __init__(self, a=0.5, b=1.0, t_max=20, dt=0.01):
        self.a = a
        self.b = b
        self.t_max = t_max
        self.dt = dt
        self.t = np.arange(0, t_max + dt, dt)

    # --- Input Functions ---
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

    # --- TASK 1: Error Function ---
    def u_error_A(self, u):
        """Adds gradual degradation and high-frequency vibration to the pump."""
        # e(t) = -0.02*t + 0.08*sin(8t)
        e_t = -0.02 * self.t + 0.08 * np.sin(8 * self.t)
        return u + e_t

    # --- Core Laplace Engine ---
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

    # --- Original Metrics ---
    def steady_state(self, h):
        idx = max(1, int(0.05 * len(h)))
        return np.mean(h[-idx:])

    def time_constant(self, h):
        h_ss = self.steady_state(h)
        target = 0.632 * h_ss
        if h_ss == 0 or (h_ss > 0 and np.max(h) < target):
            return 0.0
        for i, val in enumerate(h):
             if (h_ss > 0 and val >= target):
                return self.t[i]
        return 0.0

    def rise_time(self, h):
        h_ss = self.steady_state(h)
        if h_ss == 0: return 0.0
        low_target, high_target = 0.10 * h_ss, 0.90 * h_ss
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
        h_ss = self.steady_state(h)
        if h_ss == 0: return 0.0
        upper_bound, lower_bound = h_ss * 1.02, h_ss * 0.98
        for i in range(len(h) - 1, -1, -1):
            if h[i] > upper_bound or h[i] < lower_bound:
                return self.t[i + 1] if i + 1 < len(self.t) else self.t[-1]
        return 0.0

    def overshoot(self, h):
        h_ss = self.steady_state(h)
        if h_ss <= 0: return 0.0
        max_val = np.max(h)
        return ((max_val - h_ss) / h_ss) * 100.0 if max_val > h_ss else 0.0

    # --- TASK 2: New Metrics ---
    def integral_squared_error(self, h):
        """ISE = ∫ (h_ss - h(t))² dt"""
        h_ss = self.steady_state(h)
        integrand = (h_ss - h) ** 2
        # Reusing the Trapezoidal rule hack we learned earlier!
        ise = np.sum((integrand[:-1] + integrand[1:]) / 2.0) * self.dt
        return ise

    def response_energy(self, h):
        """E = ∫ h(t)² dt"""
        integrand = h ** 2
        # Trapezoidal rule again
        energy = np.sum((integrand[:-1] + integrand[1:]) / 2.0) * self.dt
        return energy


# ==========================================
# Execution Block
# ==========================================

# Initialise system
system = SmartIrrigation(a=0.5, b=1.0, t_max=20, dt=0.01)

# Task 1 & 3: Only apply to Step and Exponential inputs
target_inputs = {
    "Step Input": system.u_step(),
    "Exponential Input": system.u_exponential(),
}

# Bromwich contour parameters setup
c = 0.25  
W = 100.0
N = 2000  
delta_w = 2 * W / N
omega = -W + np.arange(N) * delta_w
s_list = c + 1j * omega

colors = ['#2196F3', '#FF9800']

for idx, (name, u_clean) in enumerate(target_inputs.items()):
    print(f"\n{'='*50}\nProcessing: {name}\n{'='*50}")

    # Generate the corrupted input
    u_corr = system.u_error_A(u_clean)

    # --- Laplace Simulation (Clean) ---
    print("Computing Clean Laplace...")
    U_s_clean = np.array([system.laplace_transform(u_clean, s) for s in s_list])
    H_s_clean = system.H_s(s_list, U_s_clean)
    h_clean = system.inverse_laplace(s_list, H_s_clean)

    # --- Laplace Simulation (Corrupted) ---
    print("Computing Corrupted Laplace...")
    U_s_corr = np.array([system.laplace_transform(u_corr, s) for s in s_list])
    H_s_corr = system.H_s(s_list, U_s_corr)
    h_corr = system.inverse_laplace(s_list, H_s_corr)

    # --- Print New Metrics ---
    ise_clean = system.integral_squared_error(h_clean)
    energy_clean = system.response_energy(h_clean)
    ise_corr = system.integral_squared_error(h_corr)
    energy_corr = system.response_energy(h_corr)

    print(f"\n  ► Metrics for {name}")
    print(f"      [CLEAN]      ISE: {ise_clean:.4f}  |  Energy: {energy_clean:.4f}")
    print(f"      [CORRUPTED]  ISE: {ise_corr:.4f}  |  Energy: {energy_corr:.4f}")

    # --- Plotting (Side-by-Side: Clean vs Corrupted) ---
    fig, axes = plt.subplots(1, 2, figsize=(14, 5), sharey=True)
    fig.suptitle(f"Smart Irrigation System — {name}", fontsize=14, fontweight='bold')

    # Left: Clean
    axes[0].plot(system.t, u_clean, 'k--', lw=1.5, alpha=0.6, label="Clean Input $u(t)$")
    axes[0].plot(system.t, h_clean, color=colors[idx], lw=2.2, label="Clean Output $h(t)$")
    axes[0].set_title("Original System (No Error)", fontweight='bold')
    axes[0].set_xlabel("Time (s)")
    axes[0].set_ylabel("Water Level / Input")
    axes[0].legend()
    axes[0].grid(True, alpha=0.3)

    # Right: Corrupted
    axes[1].plot(system.t, u_corr, 'r--', lw=1.5, alpha=0.6, label="Corrupted Input $u(t) + e(t)$")
    axes[1].plot(system.t, h_corr, color='tomato', lw=2.2, label="Corrupted Output $h(t)$")
    axes[1].set_title("Degraded System (Wear + Vibration)", fontweight='bold')
    axes[1].set_xlabel("Time (s)")
    axes[1].legend()
    axes[1].grid(True, alpha=0.3)

    plt.tight_layout()
    plt.show()