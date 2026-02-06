#ifndef MATRIX_MULTIPLY_VEGA_LITE_PLOT_H
#define MATRIX_MULTIPLY_VEGA_LITE_PLOT_H

#include <string>
#include <vector>

// Generates a Vega-Lite JSON specification (as a JSON string) for a line chart
// comparing two matrix multiplication algorithms across various matrix sizes.
// Each vector must have the same length; times are in microseconds.
std::string generateVegaLiteSpecJson(const std::vector<int> &sizes,
                                     const std::vector<long long> &ijk_times,
                                     const std::vector<long long> &dac_times);

// Writes an HTML file that embeds the given Vega-Lite specification JSON.
// Throws std::runtime_error if the file cannot be opened.
void generateHtml(const std::string &spec_json, const std::string &filename);

#endif
