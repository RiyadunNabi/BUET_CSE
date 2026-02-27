import tkinter as tk
from tkinter import filedialog, messagebox
import numpy as np
import scipy.io.wavfile as wav
import sounddevice as sd
from discrete_framework import DiscreteSignal, DFTAnalyzer, FastFourierTransform


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

        # Equalizer Sliders
        self.slider_frame = tk.Frame(root)
        self.slider_frame.pack(pady=20, padx=20)

        self.sliders = []
        labels = ["Low", "Low-Mid", "Mid", "High-Mid", "High"]
        for i in range(5):
            frame = tk.Frame(self.slider_frame)
            frame.pack(side=tk.LEFT, padx=5)
            tk.Label(frame, text=labels[i], font=("Arial", 8)).pack()
            slider = tk.Scale(frame, from_=2.0, to=0.0, resolution=0.1, length=150, orient=tk.VERTICAL)
            slider.set(1.0)
            slider.pack()
            self.sliders.append(slider)

    def load_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("WAV files", "*.wav")])
        if file_path:
            try:
                self.samplerate, data = wav.read(file_path)

                # Normalize to float [-1, 1]
                if data.dtype == np.int16:
                    data = data.astype(np.float32) / 32768.0
                elif data.dtype == np.int32:
                    data = data.astype(np.float32) / 2147483648.0
                elif data.dtype == np.uint8:
                    data = (data.astype(np.float32) - 128.0) / 128.0

                if data.dtype != np.float32:
                    data = data.astype(np.float32)

                # Convert to mono if stereo
                if len(data.shape) > 1:
                    data = np.mean(data, axis=1)

                self.original_audio = data
                self.processed_audio = None
                duration = len(data) / self.samplerate
                print(f"Loaded: {len(data)} samples, {self.samplerate} Hz, {duration:.1f}s")
                messagebox.showinfo("Loaded", f"Audio loaded: {duration:.1f}s @ {self.samplerate} Hz")
            except Exception as e:
                messagebox.showerror("Error", f"Could not load file: {e}")

    def process_and_play(self):
        if self.original_audio is None:
            messagebox.showwarning("Warning", "Please load a WAV file first.")
            return

        print("Starting processing...")
        gains = [s.get() for s in self.sliders]

        # Choose analyzer
        if self.use_fft.get():
            analyzer = FastFourierTransform()
            chunk_size = 1024  # Power of 2 for FFT
        else:
            analyzer = DFTAnalyzer()
            chunk_size = 256   # Smaller chunk for DFT due to O(N^2) cost

        audio = self.original_audio
        total_samples = len(audio)
        output_audio = np.zeros(total_samples, dtype=np.float64)

        num_chunks = int(np.ceil(total_samples / chunk_size))

        for i in range(num_chunks):
            start = i * chunk_size
            end = min(start + chunk_size, total_samples)
            chunk = audio[start:end]

            actual_size = len(chunk)

            # Zero-pad chunk to chunk_size if needed
            if actual_size < chunk_size:
                padded_chunk = np.zeros(chunk_size, dtype=np.complex128)
                padded_chunk[:actual_size] = chunk
            else:
                padded_chunk = chunk.astype(np.complex128)

            # 3. Frequency Analysis: compute DFT/FFT
            signal = DiscreteSignal(padded_chunk)
            spectrum = analyzer.compute_dft(signal)

            N = len(spectrum)

            # 4. Filtering: apply gain to 5 frequency bands
            # Band edges are evenly distributed across [0, N/2]
            band_edges = [0,
                          N // 10,
                          N // 5,
                          3 * N // 10,
                          2 * N // 5,
                          N // 2]

            filtered_spectrum = spectrum.copy()
            for b in range(5):
                lo = band_edges[b]
                hi = band_edges[b + 1]
                gain = gains[b]
                # Apply gain to positive frequencies
                filtered_spectrum[lo:hi] *= gain
                # Apply same gain to mirrored negative frequencies (symmetry)
                if lo > 0:
                    filtered_spectrum[N - hi:N - lo] *= gain

            # 5. Reconstruction: IDFT/IFFT
            reconstructed = analyzer.compute_idft(filtered_spectrum)

            # Take only the real part and original chunk length
            real_chunk = np.real(reconstructed[:actual_size])

            output_audio[start:end] = real_chunk

            if (i + 1) % 10 == 0:
                print(f"  Processed chunk {i + 1}/{num_chunks}")

        print("Processing complete.")

        # Normalize to prevent clipping
        max_val = np.max(np.abs(output_audio))
        if max_val > 1.0:
            output_audio = output_audio / max_val

        self.processed_audio = output_audio.astype(np.float32)

        # 7. Playback
        sd.stop()
        default_output = sd.default.device[0]
        sd.play(self.processed_audio, self.samplerate, device=default_output)
        print("Playback started.")


if __name__ == "__main__":
    root = tk.Tk()
    app = AudioEqualizer(root)
    root.mainloop()