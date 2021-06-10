import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
plt.style.use("latex.mplstyle")

def numpyArr(name):
    df = pd.read_csv(name, delimiter="\t")
    return df.to_numpy(dtype=float).transpose()

if __name__ == "__main__":
    names=["slow", "medium", "fast"]
    prefix=["", "../data/", "../data/new/", "../data/new2/"]
    data0 = []
    data1 = []
    iterations0 = [4, 20, 50]
    iterations1 = [10, 30, 100]

    scaleX = 1
    scaleY = 1
    iterTot = [iterations0, iterations1, iterations1, iterations1]

    fig, ax = plt.subplots(nrows=4, ncols=3, figsize=(10, 8))
    for lccLocal, iter in enumerate(iterTot):
        for j, n in enumerate(names):
            #if lccLocal == 0: continue
            dat = numpyArr(prefix[lccLocal] + n + ".txt")
            length = len(dat)
            if length > 2:
                maxCol = length-1
                threads = dat[0]
                times = np.mean(dat[1:maxCol], axis=0)
                err = np.std(dat[1:maxCol], axis=0) / np.sqrt(iter[j])
                ax[lccLocal][j].errorbar(scaleX * threads, scaleY * times, yerr=scaleY * err, fmt='o',
                             linewidth=0.8, capsize=2, capthick=0.6, markersize=0)
            else:
                threads = dat[0]
                times = dat[1] / iter[j]
            ax[lccLocal][j].plot(scaleX * threads, scaleY * times, "ko", markersize=2)
            ax[lccLocal][j].set_xlabel("#Threads", fontsize=10)
            ax[lccLocal][j].set_ylabel(r'$\frac{t}{s}$', fontsize=15)
            ax[lccLocal][j].tick_params(axis='both', which='major', labelsize=8)
            if lccLocal == 2: ax[lccLocal][j].set_title("Flag -O2")
            if lccLocal == 3: ax[lccLocal][j].set_title("Flag -O2 -O3")
    plt.tight_layout(pad=1.5)
    plt.savefig("lcc2_results.pdf", bbox_inches="tight")



