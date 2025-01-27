import json
from pathlib import Path
from common import plot_results, extract_data

benchmarks_path = Path(
    "results"
    # "/home/giacomo/Dropbox/Ricerca/Codes/Learning_Codes/CPP_Playground/benchmarks/results"
)
# Load the json file
with open(benchmarks_path / 'benchmarks.json', 'r') as f:
    results = json.load(f)

benchmarks = results["benchmarks"]

data_len = 8
slopes_end = data_len

benchmark_name = "operator[]"
save_plots_to_disk = True
show_plots = False
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options = dict()
plot_options["location"] = "upper left"
plot_options["print_figure_title"] = False
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
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
# plot_options["max_y"] = 50

data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "allocate_matrix"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "copy_matrix"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "apply_inplace_fun"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "LU_factorization"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_four_mat"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "long_op_1"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_STL"), extract_data(benchmarks, benchmark_name + "_CST")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "sum_four_mat"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_elwise_two_mat"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_with_scalar"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_two_expr"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "mult_two_expr_preeval"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)

benchmark_name = "long_op_2"
output_file = Path(benchmarks_path / (benchmark_name + ".png"))
plot_options["figure_title"] = benchmark_name
plot_options["slopes"] = [[0], [10], [[0, slopes_end]]]
data = [extract_data(benchmarks, benchmark_name + "_ET"), extract_data(benchmarks, benchmark_name + "_RG")]
plot_results(data, save_plots_to_disk, show_plots, output_file, plot_options)
