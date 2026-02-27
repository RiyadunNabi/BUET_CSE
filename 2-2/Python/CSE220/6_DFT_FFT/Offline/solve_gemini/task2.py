import tkinter as tk
from tkinter import filedialog, messagebox
import numpy as np
import scipy.io.wavfile as wav
import sounddevice as sd
from discrete_framework import DFTAnalyzer, FastFourierTransform, DiscreteSignal

class AudioEqualizer:
    def __init__(self, root):
        self.root = root
        self.root.title("DFT Audio Equalizer")
        
        self.samplerate = 0
        self.original_audio = None
        self.processed_audio = None
        
        # --- UI Layout ---
        top_frame = tk.Frame(root)
        top_frame.pack(pady=10)
        
        tk.Button(top_frame, text="Load WAV File", command=self.load_file).pack(side=tk.LEFT, padx=10)
        tk.Button(top_frame, text="Process & Play", command=self.process_and_play).pack(side=tk.LEFT, padx=10)
        tk.Button(top_frame, text="Stop Audio", command=sd.stop).pack(side=tk.LEFT, padx=10)
        
        # Toggle Switch
        control_frame = tk.Frame(root)
        control_frame.pack(pady=5)
        self.use_fft = tk.BooleanVar(value=False)
        tk.Label(control_frame, text="Algorithm: ").pack(side=tk.LEFT)
        tk.Radiobutton(control_frame, text="DFT (Slow)", variable=self.use_fft, value=False).pack(side=tk.LEFT)
        tk.Radiobutton(control_frame, text="FFT (Fast)", variable=self.use_fft, value=True).pack(side=tk.LEFT)
        
        # Sliders Setup (10 frequency bands)
        slider_frame = tk.Frame(root)
        slider_frame.pack(pady=10)
        self.sliders = []
        bands = ["32Hz", "64", "125", "250", "500", "1K", "2K", "4K", "8K", "16K"]
        for i, band in enumerate(bands):
            frame = tk.Frame(slider_frame)
            frame.pack(side=tk.LEFT, padx=5)
            # Default Gain is 1.0. Range 0.0 (muted) to 2.0 (boosted)
            slider = tk.Scale(frame, from_=2.0, to=0.0, resolution=0.1, orient=tk.VERTICAL)
            slider.set(1.0)
            slider.pack()
            self.sliders.append(slider)
            tk.Label(frame, text=band).pack()

    def load_file(self):
        filepath = filedialog.askopenfilename(filetypes=[("WAV files", "*.wav")])
        if filepath:
            try:
                self.samplerate, data = wav.read(filepath)
                if data.dtype != np.float32:
                    # Normalize and convert to float32
                    if data.dtype == np.int16:
                        data = data.astype(np.float32) / 32768.0
                    else:
                        data = data.astype(np.float32)
                if len(data.shape) > 1: # Convert to mono
                    data = np.mean(data, axis=1)
                
                self.original_audio = data
                self.processed_audio = None
                print(f"Loaded: {len(data)} samples, {self.samplerate} Hz")
            except Exception as e:
                messagebox.showerror("Error", f"Could not load file: {e}")

    def process_and_play(self):
        if self.original_audio is None:
            messagebox.showwarning("Warning", "Please load a WAV file first.")
            return
        
        print("Starting processing...")
        gains = [s.get() for s in self.sliders]
        
        # Select target chunk size that is a power of 2
        chunk_size = 2048 
        analyzer = FastFourierTransform() if self.use_fft.get() else DFTAnalyzer()
        
        audio = self.original_audio
        output_audio = np.zeros_like(audio, dtype=np.float32)
        num_chunks = int(np.ceil(len(audio) / chunk_size))
        
        # 1. Map Equalizer Sliders to Frequency Response (H)
        H = np.ones(chunk_size, dtype=np.complex128)
        bin_width = (chunk_size // 2) // len(gains)
        
        for i, gain in enumerate(gains):
            start = i * bin_width
            end = (i + 1) * bin_width if i < len(gains) - 1 else chunk_size // 2
            
            # Apply gain to positive frequencies
            H[start:end] = gain
            # Apply identical gain to matching negative frequencies for a real signal
            H[chunk_size - end : chunk_size - start] = gain
            
        # 2. Chunking, Transform, Filter, and Overlap Add
        for i in range(num_chunks):
            start = i * chunk_size
            end = min(start + chunk_size, len(audio))
            chunk = audio[start:end]
            
            # Zero-pad if the chunk is not a full 2048
            if len(chunk) < chunk_size:
                chunk = np.pad(chunk, (0, chunk_size - len(chunk)), 'constant')
                
            signal = DiscreteSignal(chunk)
            
            # Forward Transform
            spectrum = analyzer.compute_dft(signal)
            
            # Apply Filter
            filtered_spectrum = spectrum * H
            
            # Inverse Transform
            reconstructed = np.real(analyzer.compute_idft(filtered_spectrum))
            
            # Add to output
            if end == len(audio):
                output_audio[start:end] = reconstructed[:end-start]
            else:
                output_audio[start:end] = reconstructed
                
        # 3. Prevent clipping by normalizing (only if it clips)
        max_val = np.max(np.abs(output_audio))
        if max_val > 1.0:
            output_audio = output_audio / max_val
            
        self.processed_audio = output_audio 
    
        sd.stop()
        default_output = sd.default.device[0]
        sd.play(self.processed_audio, self.samplerate, device=default_output)

if __name__ == "__main__":
    root = tk.Tk()
    app = AudioEqualizer(root)
    root.mainloop()