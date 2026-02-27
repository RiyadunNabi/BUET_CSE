import tkinter as tk
import numpy as np
import math
from discrete_framework import DiscreteSignal, DFTAnalyzer, FastFourierTransform


class DoodlingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Fourier Epicycles Doodler")

        # --- UI Layout ---
        self.canvas = tk.Canvas(root, width=800, height=600, bg="white")
        self.canvas.pack()

        control_frame = tk.Frame(root)
        control_frame.pack(pady=10)

        # Buttons
        tk.Button(control_frame, text="Clear Canvas", command=self.clear).pack(side=tk.LEFT, padx=5)
        tk.Button(control_frame, text="Draw Epicycles", command=self.run_transform).pack(side=tk.LEFT, padx=5)

        # Toggle Switch (Radio Buttons)
        self.use_fft = tk.BooleanVar(value=False)
        tk.Label(control_frame, text=" |  Algorithm: ").pack(side=tk.LEFT, padx=5)
        tk.Radiobutton(control_frame, text="Naive DFT", variable=self.use_fft, value=False).pack(side=tk.LEFT)
        tk.Radiobutton(control_frame, text="FFT", variable=self.use_fft, value=True).pack(side=tk.LEFT)

        # State Variables
        self.points = []
        self.drawing = False
        self.fourier_coeffs = None
        self.is_animating = False
        self.after_id = None
        self.num_frames = 0
        self.center_offset = (0, 0)
        self.time_step = 0
        self.path_points = []  # traced path for drawing

        # Bindings
        self.canvas.bind("<Button-1>", self.start_draw)
        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<ButtonRelease-1>", self.end_draw)

    def start_draw(self, event):
        self.is_animating = False
        if self.after_id:
            self.root.after_cancel(self.after_id)
        self.canvas.delete("all")
        self.points = []
        self.drawing = True

    def draw(self, event):
        if self.drawing:
            x, y = event.x, event.y
            self.points.append((x, y))
            r = 2
            self.canvas.create_oval(x - r, y - r, x + r, y + r, fill="black", outline="black")

    def end_draw(self, event):
        self.drawing = False

    def clear(self):
        self.canvas.delete("all")
        self.points = []
        self.is_animating = False
        if self.after_id:
            self.root.after_cancel(self.after_id)

    def draw_epicycle(self, x, y, radius):
        """
        Helper method to draw a circle (epicycle).
        x, y: Center coordinates
        radius: Radius of the circle
        """
        self.canvas.create_oval(x - radius, y - radius, x + radius, y + radius,
                                outline="blue", tags="epicycle")

    def run_transform(self):
        if not self.points:
            return

        # 1. Convert (x, y) points to complex signal
        complex_points = [complex(x, y) for x, y in self.points]
        signal = DiscreteSignal(complex_points)

        # 2. If FFT selected, interpolate to nearest power of 2
        if self.use_fft.get():
            analyzer = FastFourierTransform()
            N = len(signal)
            # Find nearest power of 2
            next_pow2 = 1
            while next_pow2 < N:
                next_pow2 <<= 1
            signal = signal.interpolate(next_pow2)
        else:
            analyzer = DFTAnalyzer()

        # 3. Compute DFT/FFT
        print(f"Computing {'FFT' if self.use_fft.get() else 'DFT'} for {len(signal)} points...")
        self.fourier_coeffs = analyzer.compute_dft(signal)
        self.num_frames = len(self.fourier_coeffs)
        print("Transform complete. Animating...")

        # Compute mean to use as offset center
        mean_x = np.mean([p[0] for p in self.points])
        mean_y = np.mean([p[1] for p in self.points])

        # Clear canvas and animate
        self.canvas.delete("all")
        self.path_points = []
        self.animate_epicycles((mean_x, mean_y))

    def animate_epicycles(self, center_offset):
        self.is_animating = True
        self.time_step = 0
        self.center_offset = center_offset
        self.update_frame()

    def update_frame(self):
        if not self.is_animating:
            return

        self.canvas.delete("epicycle")

        N = self.num_frames
        t = self.time_step / N  # normalized time in [0, 1)

        # Sort coefficients by magnitude (largest first) for visual clarity
        coeffs = self.fourier_coeffs
        indices = np.argsort(-np.abs(coeffs))

        # Starting position (center of drawing)
        cx, cy = self.center_offset

        # We'll draw epicycles from largest to smallest frequency component
        x, y = cx, cy

        for k_idx in indices:
            # Frequency index: map to signed frequency
            if k_idx <= N // 2:
                freq = k_idx
            else:
                freq = k_idx - N

            amplitude = np.abs(coeffs[k_idx]) / N
            phase = np.angle(coeffs[k_idx])

            if amplitude < 0.5:
                continue  # skip negligible components

            # Draw circle
            self.draw_epicycle(x, y, amplitude)

            # Compute next tip position
            angle = 2 * np.pi * freq * t + phase
            nx = x + amplitude * np.cos(angle)
            ny = y + amplitude * np.sin(angle)

            # Draw the rotating arm
            self.canvas.create_line(x, y, nx, ny, fill="red", tags="epicycle")

            x, y = nx, ny

        # Record and draw the traced path
        self.path_points.append((x, y))
        if len(self.path_points) > 1:
            for i in range(1, len(self.path_points)):
                x0, y0 = self.path_points[i - 1]
                x1, y1 = self.path_points[i]
                self.canvas.create_line(x0, y0, x1, y1, fill="black", width=2, tags="epicycle")

        self.time_step = (self.time_step + 1)

        # Loop animation
        if self.time_step >= N:
            self.time_step = 0
            self.path_points = []

        self.after_id = self.root.after(50, self.update_frame)


if __name__ == "__main__":
    root = tk.Tk()
    app = DoodlingApp(root)
    root.mainloop()