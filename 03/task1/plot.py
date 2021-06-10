import matplotlib.pyplot as plt
import pandas as pd


def plot_name(name, ax):
    dir_name = "./data/" + name + ".txt"
    df = pd.read_csv(dir_name, delimiter='\t')
    columns = len(df.columns) - 2
    times = df['TotalTime'].to_numpy() / columns
    threads = df['#Threads'].to_numpy()
    ax.plot(threads, times, 'bo', markersize=3)
    ax.set_title(name)
    ax.set_xlabel("Threads")
    ax.set_ylabel("Time in s")


if __name__ == "__main__":
    fig, ax_arr = plt.subplots(ncols=3, nrows=1, figsize=(7, 3))
    names = ["task1", "task2", "task3"]
    for i, ax in enumerate(ax_arr): plot_name(names[i], ax)
    fig.tight_layout()
    plt.savefig("final.pdf", bbox_inches='tight')
