import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("gc_times.txt", skiprows=1)
n  = data[:, 0].astype(int)
k  = data[:, 1].astype(int)
t  = data[:, 2]
dt = data[:, 3]

plt.figure()
plt.xlabel("n (number of vertices)")
plt.ylabel("log(t)  (t in seconds)")
plt.title("Graph colouring runtime: log(t) vs n with line fit")
plt.grid(True)

for kk in [3, 4]:
    mask = (k == kk) & (t > 0)
    nn  = n[mask]
    tt  = t[mask]
    dtt = dt[mask]

    y = np.log(tt)

    # Fit: log(t) = a*n + b   (straight line in n vs log(t))
    a, b = np.polyfit(nn, y, 1)

    print(f"k={kk}: log(t) = a*n + b")
    print(f"  a = {a}")
    print(f"  b = {b}")
    print(f"  so t ~ exp(b) * exp(a*n)\n")

    # Plot points (with approx error bars in log space: d(log t) ~ dt/t)
    yerr = np.where(tt > 0, dtt / tt, 0.0)
    plt.errorbar(nn, y, yerr=yerr, fmt='o', capsize=4, label=f"data k={kk}")

    # Plot fitted line
    nfit = np.linspace(nn.min(), nn.max(), 200)
    yfit = a * nfit + b
    plt.plot(nfit, yfit, '-', label=f"fit k={kk}: a={a:.3g}, b={b:.3g}")

plt.legend()
plt.show()
