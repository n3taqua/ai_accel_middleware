# AI Accelerator Middleware Demo Project

## 📋 Overview

This project simulates a minimal **AI Accelerator system** consisting of:

- **User-Space Software (Python Inference):** Runs a dummy AI model and sends inference results.
- **Kernel-Space Driver (Linux Kernel Module):** Provides a memory-mapped `/dev/ai_dummy` device for communication.
- **Hardware Accelerator (Verilog MAC3 Module):** Emulates a simple Multiply–Accumulate operation.

Although running separately in this demo, these components model a typical **Middleware + Driver + Hardware Accelerator** flow in real systems.

---

## 🏗️ Project Structure

| Folder         | Content                                           |
|----------------|---------------------------------------------------|
| `driver/`      | Kernel module source (`ai_dummy.c`) + Makefile    |
| `user_space/`  | Python Inference script (`infer_client.py`)       |
| `verilog/`     | Verilog hardware module (`mac3.v`) and testbench (`tb_mac3.v`) |
| `diagrams/`    | (Optional) System flow diagrams                   |

---

## 🚀 Flow Summary

1. **Python Inference:**
   - Runs a dummy PyTorch model.
   - (Intended) Writes inference output into `/dev/ai_dummy` via mmap (simulated).

2. **Kernel Module:**
   - Provides a dummy mmap-able device `/dev/ai_dummy`.

3. **Hardware Accelerator (Verilog):**
   - MAC module simulates Multiply–Accumulate logic.
   - Testbench manually drives inputs and verifies output.

> **Note:**  
> Due to WSL2 limitations, Kernel driver loading is not available.  
> Full integration can be achieved in a native Ubuntu or virtualized Linux environment.

---

## 🛠️ Setup and Build

### Requirements
- Ubuntu Linux or WSL2 (Ubuntu 20.04)
- Python 3.x with `torch`, `numpy`
- GCC, Make
- Icarus Verilog (`iverilog`, `vvp`)
- GTKWave (optional for waveform visualization)

### Build and Run

#### 1. Kernel Driver
```bash
cd driver
make
# sudo insmod ai_dummy.ko  (Skip on WSL2)
```

#### 2. User-Space Inference
```bash
cd user_space
source venv/bin/activate
python infer_client.py
```

#### 3. Verilog Hardware Accelerator
```bash
cd verilog
iverilog -o tb_mac3 tb_mac3.v mac3.v
vvp tb_mac3
# gtkwave wave.vcd (Optional to view waveform)
```

---

## 📈 Waveform Verification

- Open `wave.vcd` using GTKWave.
- Insert signals (`in1`, `in2`, `in3`, `w1`, `w2`, `w3`, `out`) into the waveform view.
- Verify Multiply–Accumulate calculation:

```plaintext
out = (in1 × w1) + (in2 × w2) + (in3 × w3)
```

---

## 📢 Future Improvements

- Connect Python output to Verilog input via file I/O or IPC.
- Expand MAC module to a full AI Accelerator design.
- Integrate with a real FPGA or SoC development board.

---

## 📚 Conclusion

This project demonstrates my understanding of:

- User-Space ↔ Kernel-Space interaction
- Linux device driver development
- Hardware Accelerator integration (basic)
- System-level thinking in AI infrastructure and Middleware

It lays a strong foundation for future work in Middleware, System Software, or AI Hardware Accelerator fields.

---

## 📸
```
[Python Inference] --> [Kernel Driver /dev/ai_dummy] --> [Verilog MAC Accelerator]
```
---
