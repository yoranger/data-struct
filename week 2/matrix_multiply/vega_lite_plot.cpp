#include "vega_lite_plot.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

static std::string jsonEscape(const std::string &s) {
  std::string out;
  out.reserve(s.size());
  for (const char c : s) {
    switch (c) {
      case '\\':
        out += "\\\\";
        break;
      case '"':
        out += "\\\"";
        break;
      case '\n':
        out += "\\n";
        break;
      case '\r':
        out += "\\r";
        break;
      case '\t':
        out += "\\t";
        break;
      default:
        out += c;
        break;
    }
  }
  return out;
}

std::string generateVegaLiteSpecJson(const std::vector<int> &sizes,
                                     const std::vector<long long> &ijk_times,
                                     const std::vector<long long> &dac_times) {
  if (sizes.size() != ijk_times.size() || sizes.size() != dac_times.size()) {
    throw std::invalid_argument(
        "sizes, ijk_times, and dac_times must have the same length");
  }

  std::ostringstream values;
  values << '[';
  bool first = true;
  for (std::size_t i = 0; i < sizes.size(); ++i) {
    if (!first) {
      values << ',';
    }
    first = false;

    values << '{' << "\"Matrix Size\":" << sizes[i] << ','
           << "\"Running Time (\u00b5s)\":" << ijk_times[i] << ','
           << "\"Algorithm\":\"Triple loop (ijk)\"" << '}';

    values << ',' << '{' << "\"Matrix Size\":" << sizes[i] << ','
           << "\"Running Time (\u00b5s)\":" << dac_times[i] << ','
           << "\"Algorithm\":\"8-fold recursion\"" << '}';
  }
  values << ']';

  std::ostringstream spec;
  spec << '{'
       << "\"$schema\":\"https://vega.github.io/schema/vega-lite/v5.json\","
       << "\"title\":{\"text\":\"Matrix Multiplication Running "
          "Times\",\"fontSize\":20},"
       << "\"description\":\"Median running time vs matrix size\","
       << "\"width\":800,\"height\":450,"
       << "\"data\":{\"values\":" << values.str() << "},"
       << "\"mark\":{\"type\":\"line\",\"point\":true},"
       << "\"encoding\":{"
       << "\"x\":{\"field\":\"Matrix Size\",\"type\":\"quantitative\","
          "\"title\":\"Matrix size (n for "
          "n\u00d7n)\",\"scale\":{\"type\":\"log\"},\"axis\":{"
          "\"titleFontSize\":16,\"labelFontSize\":14}},"
       << "\"y\":{\"field\":\"Running Time "
          "(\u00b5s)\",\"type\":\"quantitative\","
          "\"title\":\"Median running time "
          "(\u00b5s)\",\"scale\":{\"type\":\"log\"},\"axis\":{"
          "\"titleFontSize\":16,\"labelFontSize\":14}},"
       << "\"color\":{\"field\":\"Algorithm\",\"type\":\"nominal\","
          "\"title\":\"Algorithm\",\"legend\":{\"titleFontSize\":16,"
          "\"labelFontSize\":14}},"
       << "\"tooltip\":[{\"field\":\"Matrix Size\",\"type\":\"quantitative\"},"
          "{\"field\":\"Running Time (\u00b5s)\",\"type\":\"quantitative\"},"
          "{\"field\":\"Algorithm\",\"type\":\"nominal\"}]"
       << "}" << '}';

  return spec.str();
}

void generateHtml(const std::string &spec_json, const std::string &filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  const std::string escaped_spec = jsonEscape(spec_json);

  file << "<!DOCTYPE html>\n"
          "<html>\n"
          "  <head>\n"
          "    <meta charset=\"utf-8\"/>\n"
          "    <title>Vega-Lite Plot</title>\n"
          "    <script src=\"https://cdn.jsdelivr.net/npm/vega@5\"></script>\n"
          "    <script "
          "src=\"https://cdn.jsdelivr.net/npm/vega-lite@5\"></script>\n"
          "    <script "
          "src=\"https://cdn.jsdelivr.net/npm/vega-embed@6\"></script>\n"
          "  </head>\n"
          "  <body>\n"
          "    <div id=\"vis\"></div>\n"
          "    <script type=\"text/javascript\">\n"
          "      const spec = JSON.parse(\""
       << escaped_spec
       << "\");\n"
          "      vegaEmbed('#vis', spec);\n"
          "    </script>\n"
          "  </body>\n"
          "</html>\n";
}
