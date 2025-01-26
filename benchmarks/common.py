import matplotlib
import matplotlib.pyplot as plt
import numpy as np

import os
from pathlib import Path
import matplotlib.font_manager

matplotlib.rc("font", **{"family": "TeX Gyre DejaVu Math"})
plt.rc("text", usetex=True)


def extract_data(benchmarks, key):
    extracted = [benchmark for benchmark in benchmarks if key in benchmark["name"]]
    data = {"plot_label": key, "N": [], "cpu_time": []}
    for benchmark in extracted:
        if "/" in benchmark["name"]:
            N = int(benchmark["name"].split("/")[-1])
            data["N"].append(N)
            data["cpu_time"].append(benchmark["cpu_time"])
        elif "BigO" in benchmark["name"]:
            data["cte"] = benchmark["cpu_coefficient"]
            data['big_o'] = int(benchmark["big_o"].split('^')[-1])

    # sort N array and keep the same order for cpu_time
    perm = np.argsort(data["N"])
    data["N"] = np.array(data["N"])[perm]
    data["cpu_time"] = np.array(data["cpu_time"])[perm]
    data["cpu_time"] /= 1e9  # convert ns to s
    data["cte"] /= 1e9

    return data


def get_plot_settings():
    markers = [
        "o",
        "x",
        "s",
        ">",
        ".",
        "<",
        ",",
        "1",
        "2",
        "3",
        "4",
        "v",
        "p",
        "*",
        "h",
        "H",
        "+",
        "^",
        "D",
        "d",
        "|",
        "_",
    ]
    colors = [f"C{i}" for i in range(10)]
    # colors[1], colors[2], colors[3], colors[7] = colors[2], colors[3], colors[7], colors[1]
    markerfacecolors = ["none" for _ in range(len(colors))]
    # markerfacecolors[3] = colors[3]
    markersizes = [7.5 for _ in range(len(colors))]
    markeredgewidths = [1.2 for _ in range(len(colors))]
    figsize = (3, 2)
    lw = 2
    slopes_style = dict()
    slopes_style["linewidth"] = 2
    slopes_style["linestyle"] = [
        "--",
        "-.",
        "-",
        ":",
    ]
    slopes_style["color"] = ["k", "k", "k", "k"]
    return markers, markerfacecolors, markersizes, markeredgewidths, colors, figsize, lw, slopes_style


def export_legend_image(legend, filename="legend.png"):
    fig = legend.figure
    fig.canvas.draw()
    bbox = legend.get_window_extent().transformed(fig.dpi_scale_trans.inverted())
    fig.savefig(filename, dpi="figure", bbox_inches=bbox)


def label_from_key(key):
    if key == "dt":
        return r"$\Delta t$"
    else:
        return key


def plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options):
    location = plot_options["location"]
    legend_outside = plot_options["legend_outside"] if "legend_outside" in plot_options else False
    figure_title = plot_options["figure_title"]
    show_legend = plot_options["show_legend"]
    logx = plot_options["logx"]
    logy = plot_options["logy"]
    log_base = plot_options["log_base"] if "log_base" in plot_options else 10
    max_y = plot_options["max_y"] if "max_y" in plot_options else None
    min_y = plot_options["min_y"] if "min_y" in plot_options else None
    slopes = plot_options["slopes"] if "slopes" in plot_options else None
    set_x_label = plot_options["set_x_label"] if "set_x_label" in plot_options else False
    set_y_label = plot_options["set_y_label"] if "set_y_label" in plot_options else False
    set_x_ticks_formatter = plot_options["set_x_ticks_formatter"] if "set_x_ticks_formatter" in plot_options else None
    set_y_ticks_formatter = plot_options["set_y_ticks_formatter"] if "set_y_ticks_formatter" in plot_options else None
    set_x_ticks_labels = plot_options["set_x_ticks_labels"] if "set_x_ticks_labels" in plot_options else False
    set_y_ticks_labels = plot_options["set_y_ticks_labels"] if "set_y_ticks_labels" in plot_options else False
    xticks = plot_options["xticks"] if "xticks" in plot_options else None
    yticks = plot_options["yticks"] if "yticks" in plot_options else None
    export_legend = plot_options["export_legend"] if "export_legend" in plot_options else False
    markers, markerfacecolors, markersizes, markeredgewidths, colors, figsize, lw, slopes_style = get_plot_settings()

    if "figsize" in plot_options:
        figsize = plot_options["figsize"]

    fig, ax = plt.subplots(figsize=figsize)
    if logx:
        ax.set_xscale("log", base=log_base)
    if logy:
        ax.set_yscale("log", base=log_base)

    x_label = "$N$"
    y_label = "CPU time [s]"

    # all_res is a list of dictionaries, each dictionary will generate a curve in the plot

    ax1 = []
    ax2 = []
    min_ax2 = []
    max_ax2 = -np.inf
    cte = -np.inf
    big_o = []
    for i, results in enumerate(data):
        ax1.append(results["N"])
        ax2.append(results["cpu_time"])
        label = results["plot_label"]
        min_ax2.append(min(ax2[-1]))
        max_ax2 = max(max_ax2, max(ax2[-1]))
        cte = max(cte, results["cte"])
        big_o.append(results["big_o"])
        ax.plot(
            ax1[-1],
            ax2[-1],
            label=label.split("_")[-1],
            linewidth=lw,
            marker=markers[i],
            color=colors[i],
            markerfacecolor=markerfacecolors[i],
            markeredgewidth=markeredgewidths[i],
            markersize=markersizes[i],
        )

    if slopes is not None:
        assert big_o[:-1] == big_o[1:], "Big O must be the same for all curves"
        slope = big_o[0]
        for i, (j, fac, n) in enumerate(zip(*slopes)):
            ax1_np = np.array(ax1[j])
            ax1_np = ax1_np[n[0] : n[1]]
            ax.plot(
                ax1_np,
                # fac * min_ax2[j] * (ax1_np / ax1_np[-1]) ** slope,
                fac * cte * ax1_np**slope,
                linewidth=slopes_style["linewidth"],
                linestyle=slopes_style["linestyle"][i],
                color=slopes_style["color"][i],
                label=rf"$\mathcal{{O}}(N^{{{slope}}})$",
            )

    if set_x_ticks_formatter is not None:
        ax.xaxis.set_major_formatter(set_x_ticks_formatter)
    if set_y_ticks_formatter is not None:
        ax.yaxis.set_major_formatter(set_y_ticks_formatter)

    ax.xaxis.set_minor_formatter('')
    ax.yaxis.set_minor_formatter('')

    fs_label = 12
    fs_tick = 12
    if set_x_label:
        ax.set_xlabel(x_label, fontsize=fs_label)  # , labelpad=-0.5)
    if set_y_label:
        ax.set_ylabel(y_label, fontsize=fs_label)  # , labelpad=-0.5)
    ax.tick_params(axis="x", labelsize=fs_tick)  # , pad=1)
    ax.tick_params(axis="y", labelsize=fs_tick)  # , pad=0)
    ax.set_ylim([min_y, max_y])

    def merge_ax(ax):
        merged_ax = list(ax[0])
        for i in range(1, len(ax)):
            for j in range(len(list(ax[i]))):
                if not np.any(np.isclose(merged_ax, ax[i][j])):
                    merged_ax.append(ax[i][j])
        merged_ax.sort()
        return merged_ax

    merged_ax1 = merge_ax(ax1)
    merged_ax2 = merge_ax(ax2)

    if set_x_ticks_labels:
        if xticks is not None:
            ax.set_xticks(xticks)
        else:
            ax.set_xticks(merged_ax1[: len(merged_ax1) : 2])
    if set_y_ticks_labels:
        if yticks is not None:
            ax.set_yticks(yticks)
        else:
            ax.set_yticks(merged_ax2)

    if figure_title != "":
        ax.set_title(figure_title)

    ax.legend(loc=location, facecolor='white', framealpha=0.95)

    # if save_plots_to_disk and export_legend:
    #     legend_file_name = output_file.with_name(output_file.stem + "_legend.pdf")
    #     export_legend_image(ax.get_legend(), legend_file_name)

    if not show_legend:
        ax.get_legend().remove()

    if show_plots:
        plt.show()

    if save_plots_to_disk:
        if not output_file.parent.is_dir():
            os.makedirs(output_file.parent, exist_ok=True)
        fig.savefig(output_file, bbox_inches="tight", format="png")

    plt.close(fig)
