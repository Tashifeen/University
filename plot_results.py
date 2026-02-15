import numpy as np
import matplotlib.pyplot as plt

filename = "results.txt"

data = np.loadtxt(filename, skiprows=1)
if data.ndim == 1:
    data = data.reshape(1, -1)

n = data[:, 0]
t = data[:, 1]
has_dt = (data.shape[1] >= 3)
dt = data[:, 2] if has_dt else None

# Keep only valid points (n>0, t>0)
mask = (n > 0) & (t > 0)
n = n[mask]
t = t[mask]
if has_dt:
    dt = dt[mask]

# ---- Quadratic fit on original scale: t = c2*n^2 + c1*n + c0 ----
# If dt exists, do a weighted least squares fit (more sensible)
if has_dt:
    # weights in np.polyfit are w ~ 1/sigma
    w = np.where(dt > 0, 1.0 / dt, 0.0)
    coeffs = np.polyfit(n, t, deg=2, w=w)
else:
    coeffs = np.polyfit(n, t, deg=2)

c2, c1, c0 = coeffs
print("Quadratic fit: t = c2*n^2 + c1*n + c0")
print(f"c2 = {c2}")
print(f"c1 = {c1}")
print(f"c0 = {c0}")

# Smooth curve for plotting the fitted quadratic
n_fit = np.linspace(n.min(), n.max(), 400)
t_fit = np.polyval(coeffs, n_fit)

# ---- Plot (original linear axes) ----
plt.figure()

if has_dt:
    plt.errorbar(n, t, yerr=dt, fmt='o', capsize=4, label="data")
else:
    plt.plot(n, t, 'o', label="data")

plt.plot(n_fit, t_fit, '-', label="quadratic fit")

plt.xlabel("n")
plt.ylabel("t (seconds)")
plt.title("Runtime vs n with quadratic fit (original scale)")
plt.grid(True)
plt.legend()
plt.show()
