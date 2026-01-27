import numpy as np
import matplotlib.pyplot as plt

T_MIN, T_MAX, N = -4.0, 4.0, 4001

def x_of_t(t: np.ndarray) -> np.ndarray:
    """
    Base signal x(t).
    """
    # 1) Triangular pulse centered at 0
    tri0 = np.zeros_like(t, dtype=float)
    m0 = np.abs(t) <= 1.0
    tri0[m0] = 1.0 - np.abs(t[m0])

    # 2) Windowed ramp (odd-ish component)
    ramp = np.zeros_like(t, dtype=float)
    m1 = np.abs(t) <= 1.0
    ramp[m1] = t[m1]

    # 3) Shifted triangular pulse (breaks symmetry)
    tri_shift = np.zeros_like(t, dtype=float)
    u = t - 1.2
    m2 = np.abs(u) <= 1.0
    tri_shift[m2] = 1.0 - np.abs(u[m2])

    return tri0 + 0.6 * ramp + 0.4 * tri_shift


def time_reverse(x: np.ndarray) -> np.ndarray:
    """
    Given samples x(t), return samples of x(-t).
    Since t is symmetric and uniform, x(-t) is just x reversed.
    """
    return x[::-1]


def even_odd_decompose(x: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    """
    Decompose x(t) into even and odd parts using the formulas:
    xe(t) = 0.5 * (x(t) + x(-t))
    xo(t) = 0.5 * (x(t) - x(-t))
    Must call time_reverse(...) inside this function.
    """
    x_reversed = time_reverse(x)
    
    xe = 0.5 * (x + x_reversed)
    xo = 0.5 * (x - x_reversed)
    
    return xe, xo


# ----------------------------
# Provided plotting (do not modify)
# ----------------------------
def plot_three(t: np.ndarray, x: np.ndarray, xe: np.ndarray, xo: np.ndarray):
    plt.figure(figsize=(10, 6))
    plt.plot(t, x, label="x(t)", linewidth=2, alpha=0.7)
    plt.plot(t, xe, label="xe(t) (Even)", linestyle='--', linewidth=2)
    plt.plot(t, xo, label="xo(t) (Odd)", linestyle=':', linewidth=2)
    plt.title("Even–Odd Decomposition")
    plt.xlabel("t")
    plt.ylabel("Amplitude")
    plt.grid(True)
    plt.legend()


def plot_pair(t: np.ndarray, x: np.ndarray, xr: np.ndarray):
    plt.figure(figsize=(10, 6))
    plt.plot(t, x, label="x(t)")
    plt.plot(t, xr, label="x(-t)")
    plt.title("Time Reversal")
    plt.xlabel("t")
    plt.ylabel("Amplitude")
    plt.grid(True)
    plt.legend()


# ----------------------------
# Main (Implemented)
# ----------------------------
def main():
    # 1. Generate time axis t and compute x(t)
    t = np.linspace(T_MIN, T_MAX, N)
    x = x_of_t(t)

    # 2. Compute time reverse x(-t)
    xr = time_reverse(x)

    # 3. Compute even and odd components
    xe, xo = even_odd_decompose(x)

    # 4. Plot x(t), x(-t) separately
    plot_pair(t, x, xr)
    
    # 5. Plot decomposition together
    plot_three(t, x, xe, xo)

    # Show plots
    plt.show()

if __name__ == "__main__":
    main()