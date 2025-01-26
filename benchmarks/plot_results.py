import json
from pathlib import Path
from common import plot_results, extract_data

benchmarks_path = Path(
    "/home/giacomo/Dropbox/Ricerca/Codes/Learning_Codes/CPP_Playground/benchmarks/../build/benchmarks_Release"
)
# Load the json file
with open(benchmarks_path / 'benchmarks.json', 'r') as f:
    results = json.load(f)

benchmarks = results["benchmarks"]


benchmark_name = "operator[]"
save_plots_to_disk = True
show_plots = True
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options = dict()
plot_options["location"] = "upper left"
plot_options["figure_title"] = benchmark_name
plot_options["with_legend"] = True
plot_options["logx"] = True
plot_options["logy"] = True
plot_options["log_base"] = 10
plot_options["set_x_ticks_labels"] = False
plot_options["set_y_ticks_labels"] = False
plot_options["set_x_label"] = True
plot_options["set_y_label"] = True
# plot_options["xticks"]=[]
# plot_options["yticks"]=[]
# plot_options["set_x_ticks_formatter"] = '{x:.1f}'
# plot_options["set_y_ticks_formatter"] = '{x:.1f}'
plot_options["show_legend"] = True
plot_options["slopes"] = [[0], [10], [[0, 5]]]
# plot_options["max_y"] = 50

data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)


benchmark_name = "copy_matrix"
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, 5]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "apply_inplace_fun"
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, 5]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "sum_four_mat"
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, 5]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_elwise_two_mat"
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, 5]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_two_mat"
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, 5]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "LU_factorization"
output_file = Path(benchmarks_path / Path("images") / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, 5]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)
