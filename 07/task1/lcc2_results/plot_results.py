import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    data = pd.read_csv("results_parallel_05_05_2021-18_55_12.txt", delimiter='\t').to_numpy().transpose()
    n_par = data[1]
    t_par = data[0]
    data = pd.read_csv("results_sequential_05_05_2021-18_33_03.txt", delimiter='\t').to_numpy().transpose()
    n_seq = data[1]
    t_seq = data[0]

    plt.title("Results on lcc2 (for 1e6 repetitions)")
    plt.plot(n_par, t_par, '-', lw=1, label="parallel")
    plt.plot(n_seq, t_seq, '-', lw=1, label="sequential")
    plt.legend()
    plt.xlabel("n = len(a) = len(b) = len(c)")
    plt.ylabel("time in s")
    plt.savefig("results.pdf", bbox_inches="tight")