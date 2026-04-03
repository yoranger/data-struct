#pragma once
/**
 * ring.h
 * Doubly-linked circular ring representation.
 *
 * All vertices across every ring are stored in a single flat vector (the
 * "vertex pool").  Each Vertex knows its ring id and holds indices to its
 * previous and next live neighbours.  This gives O(1) neighbour access and
 * O(1) removal (just flip the alive flag and re-link neighbours).
 *
 * Ownership:
 *   RingPool is the single source of truth for the vertex data.  Other
 *   modules (Grid, APSC) refer to vertices by their integer index into
 *   RingPool::verts.
 */

#include "geometry.h"
#include <vector>

// ─── Vertex ───────────────────────────────────────────────────────────────────

struct Vertex {
    Point pt;       ///< Current 2-D position
    int   ring;     ///< Ring id this vertex belongs to
    int   prev;     ///< Index of previous live vertex in the ring
    int   next;     ///< Index of next live vertex in the ring
    int   version;  ///< Incremented whenever this vertex's neighbourhood changes
    bool  alive;    ///< False once the vertex has been collapsed away
};

// ─── RingPool ─────────────────────────────────────────────────────────────────

struct RingPool {
    std::vector<Vertex> verts;    ///< Flat vertex pool (indices never change)
    std::vector<int>    head;     ///< head[r] = any live vertex index in ring r
    int                 numRings; ///< Total number of rings
    int                 live;     ///< Current total live-vertex count

    RingPool() : numRings(0), live(0) {}

    /// Build the pool from per-ring point lists.
    /// rings[r] is an ordered list of Points for ring r.
    void build(const std::vector<std::vector<Point>>& rings) {
        numRings = static_cast<int>(rings.size());
        head.resize(numRings, -1);
        live = 0;

        int base = 0;
        for (int r = 0; r < numRings; ++r) {
            const auto& ring = rings[r];
            int sz = static_cast<int>(ring.size());
            head[r] = base;
            for (int i = 0; i < sz; ++i) {
                Vertex v;
                v.pt      = ring[i];
                v.ring    = r;
                v.prev    = base + (i - 1 + sz) % sz;
                v.next    = base + (i + 1) % sz;
                v.version = 0;
                v.alive   = true;
                verts.push_back(v);
            }
            base += sz;
            live += sz;
        }
    }

    /// Mark vertex b as dead and re-link its neighbours.
    /// Does NOT update the spatial grid — the caller must do that.
    void kill(int b) {
        int a = verts[b].prev;
        int c = verts[b].next;
        verts[a].next = c;
        verts[c].prev = a;
        verts[b].alive = false;
        ++verts[b].version;
        // fix ring head if it pointed at b
        if (head[verts[b].ring] == b)
            head[verts[b].ring] = c;
        --live;
    }

    /// Collect the live vertices of ring r in traversal order.
    std::vector<int> liveVertices(int r) const {
        std::vector<int> out;
        int start = head[r];
        // Advance to a live vertex (head should always be live after kill() fixes it)
        while (!verts[start].alive) start = verts[start].next;
        int cur = start;
        do {
            out.push_back(cur);
            cur = verts[cur].next;
        } while (cur != start);
        return out;
    }

    /// Signed area of ring r in its current simplified state.
    double ringArea(int r) const {
        double s = 0.0;
        for (int vi : liveVertices(r)) {
            s += shoelaceEdge(verts[vi].pt, verts[verts[vi].next].pt);
        }
        return 0.5 * s;
    }
};
