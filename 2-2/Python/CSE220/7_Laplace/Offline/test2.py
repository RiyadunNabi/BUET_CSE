import numpy as np

a = 0.5
b = 1.0
t_max = 20
dt = 0.01
t = np.arange(0, t_max, dt)
u = np.ones_like(t)

h_euler = np.zeros_like(t)
for n in range(len(t) - 1):
    h_euler[n + 1] = h_euler[n] + dt * (-a * h_euler[n] + b * u[n])

def test_params(c, W, N):
    dw = 2 * W / N
    w_k = -W + np.arange(N) * dw
    s_arr = c + 1j * w_k
    
    def laplace_transform(f, s):
        integrand = f * np.exp(-s * t)
        return np.sum((integrand[:-1] + integrand[1:]) / 2.0) * dt

    U_s_vals = np.array([laplace_transform(u, s) for s in s_arr])
    H_s_vals = (b / (s_arr + a)) * U_s_vals
    
    h_laplace = np.zeros_like(t, dtype=float)
    for i, t_val in enumerate(t):
        term = H_s_vals * np.exp(s_arr * t_val)
        h_laplace[i] = (dw / (2 * np.pi)) * np.sum(np.real(term))
        
    mse = np.mean((h_laplace - h_euler)**2)
    return mse

for c in [0.05, 0.1, 0.2, 0.5]:
    for W in [10, 50, 100]:
        for N in [500, 1000, 5000]:
            mse = test_params(c, W, N)
            print(f"c={c}, W={W}, N={N} -> MSE={mse}")

