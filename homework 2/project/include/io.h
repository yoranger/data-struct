#pragma once
/**
 * io.h
 * CSV input and output for the polygon simplification project.
 *
 * Input format (from the project spec):
 *   ring_id,vertex_id,x,y
 *   0,0,-0.5,-1.0
 *   ...
 *
 * Output format:
 *   ring_id,vertex_id,x,y
 *   <rows grouped by ring_id, vertex_id contiguous from 0>
 *   Total signed area in input: <value>
 *   Total signed area in output: <value>
 *   Total areal displacement: <value>
 *
 * All <value> fields are printed in C scientific notation (%e).
 */

#include "geometry.h"
#include "ring.h"
#include <string>
#include <vector>

// ─── InputRow ─────────────────────────────────────────────────────────────────

struct InputRow {
    int    ring_id, vertex_id;
    double x, y;
};

// ─── readCSV ──────────────────────────────────────────────────────────────────

/**
 * Read the input CSV file and return per-ring ordered point lists.
 *
 * @param path      Path to the CSV file.
 * @param[out] rings  rings[r] contains the ordered Points of ring r.
 * @param[out] numRings  Number of distinct ring ids found.
 */
void readCSV(const std::string& path,
             std::vector<std::vector<Point>>& rings,
             int& numRings);

// ─── writeOutput ──────────────────────────────────────────────────────────────

/**
 * Print the simplified polygon to standard output, followed by the three
 * area/displacement summary lines required by the spec.
 *
 * @param pool             The simplified ring pool.
 * @param inputArea        Total signed area of the original polygon.
 * @param totalDisplacement Accumulated areal displacement from all collapses.
 */
void writeOutput(const RingPool& pool,
                 double inputArea,
                 double totalDisplacement);
