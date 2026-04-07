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

    def inverse_laplace(self, s_list, F_s_values):
        dw = np.imag(s_list[1]) - np.imag(s_list[0]) if len(s_list) > 1 else 0
        h_t = np.zeros_like(self.t, dtype=float)
        F_s_arr = np.array(F_s_values)
        s_arr = np.array(s_list)
        for i, t in enumerate(self.t):
            term = F_s_arr * np.exp(s_arr * t)
            h_t[i] = (dw / (2 * np.pi)) * np.sum(np.real(term))
        return h_t

    def H_s(self, s, U_s):
        return (self.b / (s + self.a)) * U_s

    def steady_state(self, h):
        idx = int(0.05 * len(h))
        if idx == 0: idx = 1
        return np.mean(h[-idx:])

    def time_constant(self, h):
        h_ss = self.steady_state(h)
        target = 0.632 * h_ss
        if h_ss > 1e-4:
            idx = np.argmax(h >= target)
            return self.t[idx]
        return 0.0

    def rise_time(self, h):
        h_ss = self.steady_state(h)
        if h_ss > 1e-4:
            low = 0.1 * h_ss
            high = 0.9 * h_ss
            idx_low = np.argmax(h >= low)
            idx_high = np.argmax(h >= high)
            return self.t[idx_high] - self.t[idx_low]
        return 0.0

    def settling_time(self, h):
        h_ss = self.steady_state(h)
        if h_ss < 1e-4: return 0.0
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
        h = np.zeros_like(self.t)
        for n in range(len(self.t) - 1):
            dhdt = -self.a * h[n] + self.b * u[n]
            h[n + 1] = h[n] + self.dt * dhdt
        return h

if __name__ == "__main__":
    system = SmartIrrigation(a=0.5, b=1.0, t_max=20, dt=0.01)
    print("Testing pulse...")
    u = system.u_pulse()
    
    W = 100
    N = 2500
    dw = 2 * W / N
    c = 1.0
    w_k = -W + np.arange(N) * dw
    s_list = c + 1j * w_k
    
    U_s_vals = [system.laplace_transform(u, s) for s in s_list]
    H_s_vals = [system.H_s(s, U_s) for s, U_s in zip(s_list, U_s_vals)]
    h_laplace = system.inverse_laplace(s_list, H_s_vals)
    h_euler = system.euler_simulate(u)
    
    # Calculate MSE
    mse = np.mean((h_laplace - h_euler)**2)
    print("MSE between Laplace and Euler:", mse)
    print("Metrics laplace:", system.compute_metrics(h_laplace))
    print("Metrics euler:", system.compute_metrics(h_euler))
