import torch
import mmap
import os

# Dummy model
model = torch.nn.Sequential(
    torch.nn.Linear(3, 1)
)
model.eval()

# Dummy input
x = torch.tensor([[1.0, 2.0, 3.0]])

# Inference
with torch.no_grad():
    output = model(x)
print("Inference Output:", output.numpy())

# Map /dev/ai_dummy
fd = os.open("/dev/ai_dummy", os.O_RDWR)
m = mmap.mmap(fd, 4096, mmap.MAP_SHARED, mmap.PROT_WRITE)

# Write inference output to mmap
m.write(output.numpy().tobytes())

m.close()
os.close(fd)
