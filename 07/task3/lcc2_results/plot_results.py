import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    data = pd.read_csv("results_parallel_10_05_2021-16_08_25.txt", delimiter='\t').to_numpy().transpose()
    n_par = data[1]
    t_par = data[0]

    plt.title("Results on lcc2 (for 1e6 repetitions)")
    plt.plot(n_par, t_par, '-', lw=1)
    plt.xlabel("n = len(a) = len(b) = len(c)")
    plt.ylabel("time in s")
    plt.savefig("lcc2_results.pdf", bbox_inches="tight")