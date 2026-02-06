#ifndef VEGA_LITE_PLOT_H
#define VEGA_LITE_PLOT_H

#include <string>
#include <vector>

#include "nlohmann_json.h"  // JSON tools from https://github.com/nlohmann/json/

using json = nlohmann::json;
using namespace std;

json generate_vega_lite_spec(const vector<size_t> &sizes,
                             const vector<long long> &times1,
                             const vector<long long> &times2,
                             const vector<long long> &times3);
void generate_html(const json &spec, const string &filename);

#endif  // VEGA_LITE_PLOT_H
