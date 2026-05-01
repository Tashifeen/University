import matplotlib.pyplot as plt
import numpy as np

# Data
# n = number of nodes you entered in C++
# depths = the "Overall average" result you got for that n
n_values = np.array([5, 10, 50, 100, 500, 1000, 5000, 10000])
avg_depths = np.array([1.36, 2.39, 5.284, 6.238, 9.0694, 11.0934, 14.4038, 15.5456]) # Replace with your real results

# Calculate the fit
# We calculate log2 of n to find the linear relationship
log_n = np.log2(n_values)

# polyfit finds the slope (m) and intercept (b) for: y = m*x + b
# Here, x is log2(n) and y is avg_depth
m, b = np.polyfit(log_n, avg_depths, 1)

# Plotting
plt.figure(figsize=(10, 6))

# Plot the actual points you found
plt.scatter(n_values, avg_depths, color='blue', label='Measured Average Depth')

# Create a smooth line for the "Fit"
x_line = np.linspace(min(n_values), max(n_values), 100)
y_line = m * np.log2(x_line) + b
plt.plot(x_line, y_line, color='red', linestyle='--',
label=f'Empirical Fit: {m:.3f} * log2(n) + {b:.2f}')

# Formatting the graph
plt.xscale('log') # Makes the log-growth look like a straight line
plt.xlabel('Number of Nodes (n) - Log Scale')
plt.ylabel('Average Depth')
plt.title('Average Depth of Random BST vs. log(n)')
plt.legend()
plt.grid(True, which="both", ls="-", alpha=0.3)

plt.show()

print(f"Your empirical constant is: {m:.3f}")
print(f"Theory suggests it should be around 1.386")
