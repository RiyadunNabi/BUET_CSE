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
        
        tk.Button(control_frame, text="Clear Canvas", command=self.clear).pack(side=tk.LEFT, padx=5)
        tk.Button(control_frame, text="Draw Epicycles", command=self.run_transform).pack(side=tk.LEFT, padx=5)
        
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
        
        # Event Bindings
        self.canvas.bind("<Button-1>", self.start_draw)
        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<ButtonRelease-1>", self.stop_draw)
        
    def start_draw(self, event):
        self.drawing = True
        self.points.append((event.x, event.y))

    def draw(self, event):
        if self.drawing:
            x, y = event.x, event.y
            self.canvas.create_oval(x-2, y-2, x+2, y+2, fill="black", tags="user_draw")
            self.points.append((x, y))

    def stop_draw(self, event):
        self.drawing = False

    def clear(self):
        self.canvas.delete("all")
        self.points = []
        self.is_animating = False
        if self.after_id:
            self.root.after_cancel(self.after_id)

    def run_transform(self):
        if not self.points: return
        
        # 1. Convert (x,y) points to Complex Signal: z = x + jy
        complex_points = [x + 1j * y for x, y in self.points]
        signal = DiscreteSignal(complex_points)
        
        # 2. Re-sample to nearest power of 2 for FFT compatibility
        N = len(signal)
        next_pow2 = 1 << (N - 1).bit_length()
        signal = signal.interpolate(next_pow2)
        N_new = len(signal)
        
        # 3. Select Algorithm and Compute
        analyzer = FastFourierTransform() if self.use_fft.get() else DFTAnalyzer()
        spectrum = analyzer.compute_dft(signal)
        
        # Extract Frequency, Amplitude, and Phase (normalize amplitude)
        self.fourier_coeffs = []
        for k in range(N_new):
            # Map k to proper frequency: 0 to N/2 is positive freq, N/2 to N is negative freq
            freq = k if k < N_new / 2 else k - N_new
            c = spectrum[k] / N_new
            self.fourier_coeffs.append({
                'freq': freq,
                'amp': np.abs(c),
                'phase': np.angle(c)
            })
            
        # Sort by amplitude (largest circles drawn first for better visual stability)
        self.fourier_coeffs.sort(key=lambda x: x['amp'], reverse=True)
        
        self.canvas.delete("user_draw")
        self.animate_epicycles()

    def animate_epicycles(self):
        self.is_animating = True
        self.time_step = 0
        self.path = []
        self.N_frames = len(self.fourier_coeffs)
        self.update_frame()

    def update_frame(self):
        if not self.is_animating: return
        
        self.canvas.delete("epicycle")
        self.canvas.delete("arm")
        
        # Calculate the current time 't'
        t = self.time_step * (2 * np.pi / self.N_frames)
        
        # Traverse the epicycle chain
        x, y = 0, 0
        for coef in self.fourier_coeffs:
            prev_x, prev_y = x, y
            freq, amp, phase = coef['freq'], coef['amp'], coef['phase']
            
            x += amp * np.cos(freq * t + phase)
            y += amp * np.sin(freq * t + phase)
            
            # Draw standard UI artifacts
            self.canvas.create_oval(prev_x-amp, prev_y-amp, prev_x+amp, prev_y+amp, outline="#add8e6", tags="epicycle")
            self.canvas.create_line(prev_x, prev_y, x, y, fill="#a9a9a9", tags="arm")
            
        # Trace Path tip
        self.path.append((x, y))
        if len(self.path) > 1:
            for i in range(1, len(self.path)):
                self.canvas.create_line(self.path[i-1][0], self.path[i-1][1], self.path[i][0], self.path[i][1], fill="red", tags="epicycle")
                
        self.time_step += 1
        if self.time_step >= self.N_frames:
            self.time_step = 0
            self.path = [] # Refresh trace
            
        self.after_id = self.root.after(20, self.update_frame)

if __name__ == "__main__":
    root = tk.Tk()
    app = DoodlingApp(root)
    root.mainloop()