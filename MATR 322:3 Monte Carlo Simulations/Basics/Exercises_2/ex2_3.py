import typing as tp

import matplotlib.pyplot as plt
import numpy as np

from generators import Generator, LCG, ParkMiller, QCG


def chisq_flat(binned_data: np.ndarray):
    mean = np.sum(binned_data) / binned_data.size
    return np.sum((binned_data - mean) ** 2 / mean)


def chisq_worker():
    pass


def test_gen(gen: Generator, ax: plt.Axes, runs: int, bins: int, points: int):
    chisqs = np.empty((runs,))
    for i_run in range(runs):
        data = np.empty((points,))
        for i in range(points):
            data[i] = gen.gen()
        hist, bin_edges = np.histogram(data, bins=bins, range=(0, 1))
        chisq = chisq_flat(hist)
        chisqs[i_run] = chisq
    k = bins - 1
    print("Generator:", gen.NAME)
    print("Expected median:", k*(1 - 2/(9*k))**3)
    print("mean chisq:", np.mean(chisqs))
    print("median chisq:", np.median(chisqs))

    # Chi-squared distribution values from table for k = 99
    # alpha1 = 0.1
    # alpha2 = 0.05
    p1_up = 117.407
    p2_up = 123.225
    p1_low = 81.449
    p2_low = 77.046

    counts, bins, patches = ax.hist(chisqs)
    if isinstance(gen, ParkMiller):
        line_height = np.max(counts) + 1
        ax.vlines([p1_low, p1_up], ymin=0, ymax=line_height, label=r"$\alpha = 0.1$", color="green")
        ax.vlines([p2_low, p2_up], ymin=0, ymax=line_height, label=r"$\alpha = 0.05$", color="red")
        ax.legend()

    ax.set_xlabel(r"$\chi^2$")
    ax.set_ylabel("Occurrences")
    ax.set_title(gen.NAME)


def main():
    # Significance levels
    alpha1 = 0.1
    alpha2 = 0.05

    runs = 100
    bins = 100
    points = 10**6

    # For parallelism we have to create more than one generator
    lcg = LCG(12345)
    pm = ParkMiller(12345)
    qcg = QCG(
        seed=60249,
        m=85931,
        a=12459995,
        b=85932,
        c=30234
    )
    qcg_args = {
        "m": 85931,
        "a": 12459995,
        "b": 85932,
        "c": 30234
    }

    fig: plt.Figure
    axs: tp.List[plt.Axes]
    fig, axs = plt.subplots(1, 3, figsize=(11.7, 8.3))

    for i_gen, gen in enumerate([lcg, pm, qcg]):
        test_gen(gen, axs[i_gen], runs=runs, bins=bins, points=points)

    fig.savefig("ex2_3.pdf")
    fig.savefig("ex2_3.png")
    plt.show()


if __name__ == "__main__":
    main()
