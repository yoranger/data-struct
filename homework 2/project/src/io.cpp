/**
 * io.cpp
 * Implementation of CSV reading and output writing declared in io.h.
 */

#include "io.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

// ─── readCSV ──────────────────────────────────────────────────────────────────

void readCSV(const std::string& path,
             std::vector<std::vector<Point>>& rings,
             int& numRings) {
    std::ifstream f(path);
    if (!f) {
        std::cerr << "Error: cannot open input file '" << path << "'\n";
        std::exit(1);
    }

    // Collect raw rows.
    std::vector<InputRow> rows;
    std::string line;
    std::getline(f, line); // skip header

    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string tok;
        InputRow r{};
        std::getline(ss, tok, ','); r.ring_id   = std::stoi(tok);
        std::getline(ss, tok, ','); r.vertex_id = std::stoi(tok);
        std::getline(ss, tok, ','); r.x         = std::stod(tok);
        std::getline(ss, tok, ','); r.y         = std::stod(tok);
        rows.push_back(r);
    }

    if (rows.empty()) {
        std::cerr << "Error: input file contains no vertex rows.\n";
        std::exit(1);
    }

    // Determine ring count.
    numRings = 0;
    for (const auto& r : rows)
        numRings = std::max(numRings, r.ring_id + 1);

    // Group vertices by ring, sort by vertex_id within each ring.
    rings.resize(numRings);
    std::vector<std::vector<InputRow*>> byRing(numRings);
    for (auto& r : rows)
        byRing[r.ring_id].push_back(&r);

    for (int ri = 0; ri < numRings; ++ri) {
        auto& rr = byRing[ri];
        std::sort(rr.begin(), rr.end(),
                  [](const InputRow* a, const InputRow* b) {
                      return a->vertex_id < b->vertex_id;
                  });
        rings[ri].reserve(rr.size());
        for (const auto* v : rr)
            rings[ri].push_back({ v->x, v->y });
    }
}

// ─── writeOutput ──────────────────────────────────────────────────────────────

void writeOutput(const RingPool& pool,
                 double inputArea,
                 double totalDisplacement) {
    std::cout << "ring_id,vertex_id,x,y\n";

    double outputArea = 0.0;

    for (int r = 0; r < pool.numRings; ++r) {
        std::vector<int> live = pool.liveVertices(r);

        // Accumulate signed area.
        std::vector<Point> pts;
        pts.reserve(live.size());
        for (int vi : live) pts.push_back(pool.verts[vi].pt);
        outputArea += signedArea(pts);

        // Print vertices.
        int vid = 0;
        for (int vi : live) {
            const Point& p = pool.verts[vi].pt;
            std::cout << r << ',' << vid++ << ','
                      << std::setprecision(15) << p.x << ',' << p.y << '\n';
        }
    }

    // Summary lines (scientific notation, 6 decimal places).
    std::cout << std::scientific << std::setprecision(6)
              << "Total signed area in input: "  << inputArea          << '\n'
              << "Total signed area in output: " << outputArea         << '\n'
              << "Total areal displacement: "    << totalDisplacement  << '\n';
}
