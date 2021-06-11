import numpy as np
from matplotlib import animation
import pandas as pd
import os
import matplotlib.pyplot as plt
plt.style.use("./data/latex.mplstyle")


if __name__ == "__main__":
    circle = plt.Circle((0, 0), 1/np.sqrt(3), color='k', fill=False, lw=1)

    # get data from data file in nice shape
    particle_number = 3
    skip = 500
    dt = .0001
    df = pd.read_table("./data/analytically_stable.dat", sep=" ", header=None)
    arr = df.to_numpy(dtype = float)
    n = arr.size
    arr = arr.reshape((int(n/(particle_number * 3)), particle_number, 3))
    arr = arr[:-187000:skip]

    # create mov
    #outer = np.max(arr)
    outer = 1 / np.sqrt(3)
    fig = plt.figure(figsize=(8, 8))
    ax = plt.axes(xlim=(-1.5*outer, 1.5*outer), ylim=(-1.5*outer, 1.5*outer))
    ax.add_patch(circle)
    ax.set_xlabel(r'$x$', fontsize=14)
    ax.set_ylabel(r'$y$', fontsize=14)
    line, = ax.plot([], [], 'o', markersize=5)
    time_text = ax.text(outer, outer, '', fontsize=16)

    def init():
        line.set_data([], [])
        time_text.set_text("")
        return line, time_text

    def animate(i):
        if i % 60 == 0: print(int(100 * i / len(arr)))
        time = dt * i * skip
        pos = arr[i][:,:-1].transpose()
        line.set_data(pos[0], pos[1])
        time_text.set_text(r'$t=%.1f$' % time)
        return line, time_text

    writergif = animation.PillowWriter(fps=50)
    anim = animation.FuncAnimation(fig, animate, init_func=init, frames=len(arr), interval=40, blit=True)
    anim.save('./data/animation_stable.gif', writer=writergif)
