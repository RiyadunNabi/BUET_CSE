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
            self.canvas.create_oval(x-r, y-r, x+r, y+r, fill="black", outline="black")

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
        Helper method for students to draw a circle (epicycle).
        x, y: Center coordinates
        radius: Radius of the circle
        """
        self.canvas.create_oval(x-radius, y-radius, x+radius, y+radius, outline="blue", tags="epicycle")

    def run_transform(self):
        if not self.points: return
        
        # 1. Convert (x,y) points to Complex Signal
        complex_points = [x + 1j * y for x, y in self.points]
        signal = DiscreteSignal(complex_points)
        #
        N = len(signal)
        next_pow2 = 1 << (N - 1).bit_length()
        signal = signal.interpolate(next_pow2)
        N_new = len(signal)
        
        # 2. Select Algorithm 
        analyzer = FastFourierTransform() if self.use_fft.get() else DFTAnalyzer()
        
        # 3. Compute Transform
        spectrum = analyzer.compute_dft(signal)
        # Extract
        self.fourier_coeffs = []
        for k in range(N_new):
            freq = k if k < N_new / 2 else k - N_new
            c = spectrum[k] / N_new
            self.fourier_coeffs.append({
                'freq': freq,
                'amp': np.abs(c),
                'phase': np.angle(c)
            })
            
        self.fourier_coeffs.sort(key=lambda x: x['amp'], reverse=True)
        
        self.canvas.delete("all")
        self.animate_epicycles(0)

    def animate_epicycles(self, center_offset):
        self.is_animating = True
        self.time_step = 0
        #================
        self.num_frames = len(self.fourier_coeffs)
        self.path = []
        
        self.center_offset = center_offset
        self.update_frame()

    def update_frame(self):
        if not self.is_animating: return
        
        self.canvas.delete("epicycle") 
        self.canvas.delete("arm")
        self.canvas.delete("trace")
        
        # 1. Calculate the current time 't' based on self.time_step
        t = self.time_step * (2 * np.pi / self.num_frames)
        
        # 2. Reconstruct the signal value 'z' at time 't' 
        x, y = self.center_offset, self.center_offset
        for coef in self.fourier_coeffs:
            prev_x, prev_y = x, y
            freq, amp, phase = coef['freq'], coef['amp'], coef['phase']
            
            x += amp * np.cos(freq * t + phase)
            y += amp * np.sin(freq * t + phase)
            
            # 3. Draw the epicycles
            self.draw_epicycle(prev_x, prev_y, amp)
            self.canvas.create_line(prev_x, prev_y, x, y, fill="#a9a9a9", tags="arm")
            
        # 4. Draw the tips
        self.path.append((x, y))
        if len(self.path) > 1:
            for i in range(1, len(self.path)):
                self.canvas.create_line(self.path[i-1][0], self.path[i-1][1], 
                                        self.path[i][0], self.path[i][1], 
                                        fill="red", tags="trace")
        
        self.time_step = (self.time_step + 1)
        
        # Loop animation
        if self.time_step >= self.num_frames:
            self.time_step = 0
            self.path = []

        self.after_id = self.root.after(50, self.update_frame)

if __name__ == "__main__":
    root = tk.Tk()
    app = DoodlingApp(root)
    root.mainloop()