#pragma once
/**
 * apsc.h
 * Area-Preserving Segment Collapse (APSC) algorithm.
 *
 * Public interface:
 *
 *   computeCollapse()  — given four consecutive vertices A→B→C→D, compute
 *                        the area-preserving replacement point E and the
 *                        areal displacement of the collapse.
 *
 *   Simplifier         — orchestrates the greedy APSC loop:
 *                          1. Seeds a min-heap with all initial candidates.
 *                          2. Pops the cheapest valid collapse.
 *                          3. Checks topology (no new intersections).
 *                          4. Applies the collapse and updates neighbours.
 *                          5. Repeats until the target vertex count is reached.
 *
 * References:
 *   Kronenfeld et al. (2020), "Simplification of polylines by segment
 *   collapse: minimizing areal displacement while preserving area",
 *   International Journal of Cartography 6(1), pp. 22–46.
 */

#include "geometry.h"
#include "grid.h"
#include "ring.h"
#include <queue>
#include <vector>

// ─── Area-preserving E computation ────────────────────────────────────────────

/**
 * Compute the area-preserving collapse of the quadruplet A→B→C→D.
 *
 * The simplified sub-path A→E→D must have the same shoelace contribution
 * as A→B→C→D, i.e.:
 *   edge(A,E) + edge(E,D)  =  edge(A,B) + edge(B,C) + edge(C,D)
 *
 * This is one linear equation in E.  Kronenfeld et al. show that placing
 * E on the perpendicular bisector of AD minimises areal displacement.
 * Substituting E = midpoint(AD) + t·perp(AD) yields a unique t.
 *
 * @param A,B,C,D   Four consecutive ring vertices.
 * @param[out] displacement  Unsigned areal displacement of this collapse.
 * @param[out] E             Area-preserving replacement point.
 * @return false if the geometry is degenerate (A==D or collinear bisector).
 */
bool computeCollapse(const Point& A, const Point& B, const Point& C, const Point& D,
                     double& displacement, Point& E);

// ─── Priority-queue entry ─────────────────────────────────────────────────────

struct Candidate {
    double displacement; ///< Areal displacement of this collapse
    int    b_idx;        ///< Index of vertex B (centre of A→B→C→D)
    int    version;      ///< Snapshot of version[b] at push time (lazy invalidation)
};

struct CandCmp {
    bool operator()(const Candidate& a, const Candidate& b) const {
        return a.displacement > b.displacement; // min-heap
    }
};

using CandHeap = std::priority_queue<Candidate, std::vector<Candidate>, CandCmp>;

// ─── Simplifier ───────────────────────────────────────────────────────────────

/**
 * Greedy APSC simplifier.
 *
 * Usage:
 *   Simplifier s(pool, grid);
 *   double displacement = s.run(targetVertices);
 */
class Simplifier {
public:
    Simplifier(RingPool& pool, Grid& grid);

    /**
     * Run APSC until pool.live <= target or no valid collapse remains.
     * @return Total accumulated areal displacement.
     */
    double run(int target);

private:
    RingPool& pool_;
    Grid&     grid_;
    CandHeap  heap_;

    /// Push a candidate for the quadruplet centred on vertex b.
    void pushCandidate(int b);

    /// True if replacing A→B→C→D with A→E→D introduces no new intersections.
    bool collapseValid(int b_idx, const Point& E) const;

    /// Perform the collapse: kill B, move C to E, re-link, update grid & heap.
    void applyCollapse(int b_idx, const Point& E);
};
