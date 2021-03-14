import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
plt.style.use("./latex.mplstyle")

def numpyArr(name):
    df = pd.read_csv(name, delimiter="\t")
    return df.to_numpy(dtype=float).transpose()

if __name__ == "__main__":
    names=["slow", "medium", "fast"]
    data0 = []
    data1 = []
    iterations0 = [4, 20, 50]
    iterations1 = [2, 10, 10]

    for n in names:
        data0.append(numpyArr(n+".txt"))
        data1.append(numpyArr("../data/"+n+".txt"))
    dataTot = [data0, data1]
    iterTot = [iterations0, iterations1]

    fig, ax = plt.subplots(nrows=2, ncols=3, figsize=(7, 3))

    for j, data in enumerate(dataTot):
        for i, dat in enumerate(data):
            ax[j][i].plot(dat[0], dat[1]/iterTot[j][i], 'bo', markersize=2)
            ax[j][i].set_xlabel("#Threads", fontsize=10)
            ax[j][i].set_ylabel(r'$\frac{t}{s}$', fontsize=15)
            ax[j][i].tick_params(axis='both', which='major', labelsize=8)
            if j == 0: ax[j][i].set_title(names[i])
    #plt.show()
    plt.tight_layout(pad=1.5)
    plt.savefig("results.pdf", bbox_inches="tight")


