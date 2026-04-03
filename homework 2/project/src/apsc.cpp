/**
 * apsc.cpp
 * Implementation of the APSC algorithm declared in apsc.h.
 */

#include "apsc.h"
#include <algorithm>
#include <cmath>
#include <vector>

// ─── computeCollapse ──────────────────────────────────────────────────────────

bool computeCollapse(const Point& A, const Point& B, const Point& C, const Point& D,
                     double& displacement, Point& E) {
    // Shoelace contribution of the sub-path A→B→C→D that we want to preserve.
    double S = shoelaceEdge(A, B) + shoelaceEdge(B, C) + shoelaceEdge(C, D);

    // Midpoint and direction of AD.
    double mx = 0.5 * (A.x + D.x);
    double my = 0.5 * (A.y + D.y);
    double dx = D.x - A.x, dy = D.y - A.y;
    double len = std::hypot(dx, dy);
    if (len < 1e-15) return false; // A and D coincide — degenerate

    // Perpendicular unit vector to AD (90° CCW).
    double px = -dy / len, py = dx / len;

    // Parameterise E = (mx + t*px, my + t*py) and substitute into the
    // shoelace constraint  E.y*(A.x-D.x) + E.x*(D.y-A.y) = S :
    //   t*(py*(A.x-D.x) + px*(D.y-A.y)) = S - my*(A.x-D.x) - mx*(D.y-A.y)
    double coeff = py * (A.x - D.x) + px * (D.y - A.y);
    if (std::abs(coeff) < 1e-15) return false; // degenerate bisector

    double t = (S - my * (A.x - D.x) - mx * (D.y - A.y)) / coeff;
    E.x = mx + t * px;
    E.y = my + t * py;

    // Areal displacement = area of the region between the old path A→B→C→D
    // and the new path A→E→D, computed as the sum of unsigned triangle areas.
    displacement = std::abs(triArea(A, B, E))
                 + std::abs(triArea(B, C, E))
                 + std::abs(triArea(C, D, E));
    return true;
}

// ─── Simplifier ───────────────────────────────────────────────────────────────

Simplifier::Simplifier(RingPool& pool, Grid& grid)
    : pool_(pool), grid_(grid) {}

double Simplifier::run(int target) {
    // Seed the heap with one candidate per live vertex.
    for (int i = 0; i < static_cast<int>(pool_.verts.size()); ++i)
        pushCandidate(i);

    double totalDisplacement = 0.0;

    while (pool_.live > target && !heap_.empty()) {
        Candidate top = heap_.top();
        heap_.pop();

        int b = top.b_idx;

        // Lazy invalidation: skip stale entries.
        if (!pool_.verts[b].alive || top.version != pool_.verts[b].version)
            continue;

        int a = pool_.verts[b].prev;
        int c = pool_.verts[b].next;
        int d = pool_.verts[c].next;

        // A ring must retain at least 3 vertices (d==a means only 3 remain).
        if (d == a) continue;

        double disp;
        Point  E;
        if (!computeCollapse(pool_.verts[a].pt, pool_.verts[b].pt,
                             pool_.verts[c].pt, pool_.verts[d].pt, disp, E))
            continue;

        if (!collapseValid(b, E)) continue;

        totalDisplacement += disp;
        applyCollapse(b, E);
    }

    return totalDisplacement;
}

// ─── pushCandidate ────────────────────────────────────────────────────────────

void Simplifier::pushCandidate(int b) {
    if (!pool_.verts[b].alive) return;

    int a = pool_.verts[b].prev;
    int c = pool_.verts[b].next;
    if (c == b || a == b) return; // degenerate ring

    int d = pool_.verts[c].next;
    if (d == b || d == a) return; // ring has only 3 vertices — cannot collapse

    double disp;
    Point  E;
    if (!computeCollapse(pool_.verts[a].pt, pool_.verts[b].pt,
                         pool_.verts[c].pt, pool_.verts[d].pt, disp, E))
        return;

    heap_.push({ disp, b, pool_.verts[b].version });
}

// ─── collapseValid ────────────────────────────────────────────────────────────

bool Simplifier::collapseValid(int b_idx, const Point& E) const {
    int a_idx = pool_.verts[b_idx].prev;
    int c_idx = pool_.verts[b_idx].next;
    int d_idx = pool_.verts[c_idx].next;

    const Point& A = pool_.verts[a_idx].pt;
    const Point& D = pool_.verts[d_idx].pt;

    // Query the spatial index for all segments near the new edges A→E and E→D.
    AABB boxAE = segAABB(A, E);
    AABB boxED = segAABB(E, D);
    AABB combined = { std::min(boxAE.minx, boxED.minx),
                      std::min(boxAE.miny, boxED.miny),
                      std::max(boxAE.maxx, boxED.maxx),
                      std::max(boxAE.maxy, boxED.maxy) };

    std::vector<int> cands;
    grid_.query(combined, cands);

    for (int vi : cands) {
        if (!pool_.verts[vi].alive) continue;
        int ni = pool_.verts[vi].next;

        // Skip the three segments being removed (A→B, B→C, C→D)
        // and segments whose endpoint is one of the collapsing vertices
        // (they share A or D, so adjacency prevents a crossing).
        if (vi == a_idx || vi == b_idx || vi == c_idx) continue;
        if (ni == a_idx || ni == b_idx || ni == c_idx) continue;
        if (vi == d_idx) continue; // D→next(D) is adjacent to E→D

        const Point& P = pool_.verts[vi].pt;
        const Point& Q = pool_.verts[ni].pt;

        AABB boxPQ = segAABB(P, Q);
        if (aabbOverlap(boxAE, boxPQ) && segmentsIntersect(A, E, P, Q)) return false;
        if (aabbOverlap(boxED, boxPQ) && segmentsIntersect(E, D, P, Q)) return false;
    }
    return true;
}

// ─── applyCollapse ────────────────────────────────────────────────────────────

void Simplifier::applyCollapse(int b_idx, const Point& E) {
    int a_idx = pool_.verts[b_idx].prev;
    int c_idx = pool_.verts[b_idx].next;
    int d_idx = pool_.verts[c_idx].next;

    // Remove the three affected segments from the spatial index.
    grid_.remove(a_idx, pool_); // A→B
    grid_.remove(b_idx, pool_); // B→C
    grid_.remove(c_idx, pool_); // C→D

    // Kill B (unlinks it from the ring and decrements pool_.live).
    pool_.kill(b_idx);

    // Move C to the position of E and re-link: A ↔ E(C) ↔ D.
    pool_.verts[c_idx].pt   = E;
    pool_.verts[c_idx].prev = a_idx;
    pool_.verts[c_idx].next = d_idx;
    pool_.verts[a_idx].next = c_idx;
    pool_.verts[d_idx].prev = c_idx;

    // Bump versions so stale heap entries referencing A, E, D are discarded.
    ++pool_.verts[a_idx].version;
    ++pool_.verts[c_idx].version;
    ++pool_.verts[d_idx].version;

    // Insert the two new segments A→E and E→D into the spatial index.
    grid_.insert(a_idx, pool_);
    grid_.insert(c_idx, pool_);

    // Push fresh candidates for the four quadruplets now affected:
    //   prev(A)→A→E→D,  A→E→D→next(D),  and the two around E.
    pushCandidate(pool_.verts[a_idx].prev);
    pushCandidate(a_idx);
    pushCandidate(c_idx); // E
    pushCandidate(d_idx);
}
