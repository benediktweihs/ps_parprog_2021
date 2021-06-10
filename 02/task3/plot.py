import matplotlib.pyplot as plt

if __name__ == "__main__":
    arr = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    times = [16.387242896/100, 0.504251336, 9.359194566, 2.037957544, 2.583799666, 3.823345572, 4.521127453, 4.811339630, 5.277224968]
    plt.plot(arr, times)
    plt.savefig("plot_times.pdf")