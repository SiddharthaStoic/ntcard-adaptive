import pandas as pd
import matplotlib.pyplot as plt

# Load CSV
df = pd.read_csv("benchmark_results.csv")

# Create pivot table for grouped bar chart
pivot_df = df.pivot(index="K", columns="Dataset", values="Time (s)")

# Plot settings
pivot_df.plot(kind="bar", figsize=(10, 6))
plt.title("ntCard Adaptive Hashing Benchmark")
plt.xlabel("k-mer Length (k)")
plt.ylabel("Time (seconds)")
plt.xticks(rotation=0)
plt.legend(title="Dataset", bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()

# Save plot
plt.savefig("benchmark_plot.png", dpi=300)
plt.show()