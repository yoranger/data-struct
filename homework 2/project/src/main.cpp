/**
 * main.cpp
 * Entry point for the polygon simplification program.
 *
 * Usage:
 *   ./simplify <input_file.csv> <target_vertices>
 *
 * Pipeline:
 *   1. Parse arguments.
 *   2. Read input CSV → per-ring Point lists.
 *   3. Compute input signed area.
 *   4. Build RingPool (doubly-linked circular lists).
 *   5. Build Grid spatial index.
 *   6. If already at/below target, output as-is.
 *   7. Otherwise run APSC simplification loop.
 *   8. Write output CSV + summary lines.
 */

#include "apsc.h"
#include "geometry.h"
#include "grid.h"
#include "io.h"
#include "ring.h"

#include <algorithm>
#include <iostream>
#include <limits>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./simplify <input_file.csv> <target_vertices>\n";
        return 1;
    }

    const std::string inputPath = argv[1];
    const int         target    = std::stoi(argv[2]);

    // ── 1. Read input ──────────────────────────────────────────────────────
    std::vector<std::vector<Point>> ringPts;
    int numRings = 0;
    readCSV(inputPath, ringPts, numRings);

    // ── 2. Compute input signed area ───────────────────────────────────────
    double inputArea = 0.0;
    for (const auto& pts : ringPts)
        inputArea += signedArea(pts);

    // ── 3. Count total input vertices ──────────────────────────────────────
    int totalVerts = 0;
    for (const auto& pts : ringPts)
        totalVerts += static_cast<int>(pts.size());

    // ── 4. Early exit: already at/below target ─────────────────────────────
    if (totalVerts <= target) {
        // Build a pool just for output convenience.
        RingPool pool;
        pool.build(ringPts);
        writeOutput(pool, inputArea, 0.0);
        return 0;
    }

    // ── 5. Build RingPool ──────────────────────────────────────────────────
    RingPool pool;
    pool.build(ringPts);

    // ── 6. Build spatial index ─────────────────────────────────────────────
    double minx =  1e18, miny =  1e18;
    double maxx = -1e18, maxy = -1e18;
    for (const auto& pts : ringPts)
        for (const auto& p : pts) {
            minx = std::min(minx, p.x); miny = std::min(miny, p.y);
            maxx = std::max(maxx, p.x); maxy = std::max(maxy, p.y);
        }

    Grid grid;
    grid.build(minx, miny, maxx, maxy, totalVerts);
    grid.populate(pool);

    // ── 7. Run APSC ────────────────────────────────────────────────────────
    Simplifier simplifier(pool, grid);
    double totalDisplacement = simplifier.run(target);

    // ── 8. Write output ────────────────────────────────────────────────────
    writeOutput(pool, inputArea, totalDisplacement);

    return 0;
}
