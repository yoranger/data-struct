#pragma once
/**
 * grid.h
 * Uniform-grid spatial index for fast segment-intersection queries.
 *
 * Segments are stored by their start-vertex index (vi → vi.next).
 * The grid maps each segment to all grid cells its AABB overlaps.
 *
 * Complexity:
 *   Build  : O(n)
 *   Insert : O(1) amortised (few cells per segment)
 *   Remove : O(cells touched) ≈ O(1) amortised
 *   Query  : O(sqrt(n)) candidates amortised for uniformly distributed data
 *
 * The grid dimensions are set to ~sqrt(n/4) × sqrt(n/4) cells so that
 * each cell contains a roughly constant number of segments on average.
 */

#include "geometry.h"
#include "ring.h"
#include <algorithm>
#include <cmath>
#include <vector>

struct Grid {
    double ox, oy;      ///< Grid origin (lower-left corner)
    double cellW, cellH;
    int    cols, rows;
    std::vector<std::vector<int>> cells; ///< cell → list of segment-start vertex indices

    /// Build an empty grid covering [minx,maxx]×[miny,maxy] for n segments.
    void build(double minx, double miny, double maxx, double maxy, int n) {
        ox = minx; oy = miny;
        int side = std::max(1, static_cast<int>(std::sqrt(static_cast<double>(n) / 4.0)));
        cols = side; rows = side;
        cellW = (maxx - minx) / cols + 1e-9;
        cellH = (maxy - miny) / rows + 1e-9;
        cells.assign(cols * rows, {});
    }

    /// Populate the grid with every segment from the ring pool.
    void populate(const RingPool& pool) {
        for (int vi = 0; vi < static_cast<int>(pool.verts.size()); ++vi) {
            if (pool.verts[vi].alive)
                insert(vi, pool);
        }
    }

    /// Insert segment vi→next(vi) into the grid.
    void insert(int vi, const RingPool& pool) {
        const Point& a = pool.verts[vi].pt;
        const Point& b = pool.verts[pool.verts[vi].next].pt;
        int c0, c1, r0, r1;
        cellRange(segAABB(a, b), c0, c1, r0, r1);
        for (int r = r0; r <= r1; ++r)
            for (int c = c0; c <= c1; ++c)
                cells[r * cols + c].push_back(vi);
    }

    /// Remove segment vi→next(vi) from the grid.
    /// Uses the *current* endpoint positions (call before moving/killing).
    void remove(int vi, const RingPool& pool) {
        const Point& a = pool.verts[vi].pt;
        const Point& b = pool.verts[pool.verts[vi].next].pt;
        int c0, c1, r0, r1;
        cellRange(segAABB(a, b), c0, c1, r0, r1);
        for (int r = r0; r <= r1; ++r)
            for (int c = c0; c <= c1; ++c) {
                auto& cell = cells[r * cols + c];
                cell.erase(std::remove(cell.begin(), cell.end(), vi), cell.end());
            }
    }

    /// Return all segment-start indices whose AABB overlaps the query box.
    /// Duplicates (a segment spanning multiple cells) are removed.
    void query(const AABB& box, std::vector<int>& out) const {
        int c0, c1, r0, r1;
        cellRange(box, c0, c1, r0, r1);
        for (int r = r0; r <= r1; ++r)
            for (int c = c0; c <= c1; ++c)
                for (int vi : cells[r * cols + c])
                    out.push_back(vi);
        std::sort(out.begin(), out.end());
        out.erase(std::unique(out.begin(), out.end()), out.end());
    }

private:
    void cellRange(const AABB& box, int& c0, int& c1, int& r0, int& r1) const {
        c0 = std::max(0, static_cast<int>((box.minx - ox) / cellW));
        c1 = std::min(cols - 1, static_cast<int>((box.maxx - ox) / cellW));
        r0 = std::max(0, static_cast<int>((box.miny - oy) / cellH));
        r1 = std::min(rows - 1, static_cast<int>((box.maxy - oy) / cellH));
    }
};
