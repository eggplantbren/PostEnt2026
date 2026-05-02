import numpy as np

logzs  = np.atleast_1d(np.loadtxt("logzs.txt"))
logzs2 = np.atleast_1d(np.loadtxt("logzs2.txt"))

# Truncate to equal length
logzs = logzs[0:len(logzs2)]

# Calculate entropy
diffs = logzs - logzs2
print(f"Number of runs = {len(diffs)}.")
H = np.mean(diffs)
sem = np.std(diffs, ddof=1)/np.sqrt(len(diffs))
print(f"H = {H} +- {sem}.")
