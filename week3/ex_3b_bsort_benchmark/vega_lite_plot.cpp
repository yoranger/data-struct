// This file contains functions to generate Vega-Lite specifications and HTML
// files for visualizing the running time comparison of different sorting
// algorithms:
// * `generate_vega_lite_spec()` creates a Vega-Lite JSON specification for
//   plotting the running times of bubble sort, insertion sort, and merge sort.
// * `generate_html()` generates an HTML file that embeds the Vega-Lite plot
//   using the generated specification.
#include "vega_lite_plot.h"

#include <fstream>

#include "nlohmann_json.h"

using namespace std;

json generate_vega_lite_spec(const vector<size_t> &a_sizes,
                             const vector<long long> &times1,
                             const vector<long long> &times2,
                             const vector<long long> &times3) {
  // The `spec` variable holds the Vega-Lite specification for the plot.
  nlohmann::json spec = {
      {"$schema", "https://vega.github.io/schema/vega-lite/v5.json"},
      {"description", "Running Time Comparison of Sorting Algorithms"},
      {"width", 480},
      {"height", 360},
      {"background", nullptr},  // Set the background to transparent
      {"data", {{"values", nlohmann::json::array()}}},
      {"mark", {{"type", "line"}, {"point", true}}},
      {"encoding",
       {{"x",
         {{"field", "Array Size"},
          {"type", "quantitative"},
          {"scale", {{"type", "log"}}},
          {"axis", {{"title", "Array Size (log scale)"}}}}},
        {"y",
         {{"field", "Running Time"},
          {"type", "quantitative"},
          {"scale", {{"type", "log"}}},
          {"axis", {{"title", "Running Time (ms, log scale)"}}}}},
        {"color",
         {{"field", "Algorithm"},
          {"type", "nominal"},
          {"sort", {"Naive MatMul", "Div&Conq MatMul"}}}},
        {"tooltip",
         nlohmann::json::array({{{"field", "Array Size"},
                                 {"type", "quantitative"},
                                 {"title", "Array Size"}},
                                {{"field", "Running Time"},
                                 {"type", "quantitative"},
                                 {"title", "Running Time (ms)"}}})}}}};

  // Helper function to add data points
  auto add_data_point = [&](const string &algorithm, size_t array_size,
                            long long running_time) {
    if (running_time > 0) {
      spec["data"]["values"].push_back({{"Array Size", array_size},
                                        {"Running Time", running_time},
                                        {"Algorithm", algorithm}});
    }
  };

  // Loop over array sizes
  for (size_t i = 0; i < a_sizes.size(); ++i) {
    add_data_point("Min.T", a_sizes[i], times1[i]);
    add_data_point("Typ.T", a_sizes[i], times2[i]);
    add_data_point("Max.T", a_sizes[i], times3[i]);
  }
  return spec;
}

// Function to generate an HTML file that embeds a Vega-Lite plot using the
// provided JSON specification. The HTML file includes the necessary scripts to
// render the plot in a web browser.
void generate_html(const nlohmann::json &spec, const string &filename) {
  ofstream file(filename);
  file << R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Vega-Lite Plot</title>
    <script src="https://cdn.jsdelivr.net/npm/vega@5"></script>
    <script src="https://cdn.jsdelivr.net/npm/vega-lite@5"></script>
    <script src="https://cdn.jsdelivr.net/npm/vega-embed@6"></script>
</head>
<body>
    <div id="vis"></div>
    <script type="text/javascript">
        const spec = )"
       << spec.dump(4) << R"(;
        vegaEmbed('#vis', spec).catch(console.error);
    </script>
</body>
</html>
)";
  file.close();
}
