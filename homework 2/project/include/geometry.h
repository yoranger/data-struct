#pragma once
/**
 * geometry.h
 * Basic geometric types and primitives used throughout the project.
 *
 * Provides:
 *  - Point          : 2-D coordinate
 *  - AABB           : axis-aligned bounding box for spatial queries
 *  - triArea        : signed area of a triangle
 *  - signedArea     : shoelace signed area of a polygon ring
 *  - shoelaceEdge   : single directed-edge contribution to the shoelace sum
 *  - segmentsIntersect : proper (non-touching) segment–segment intersection test
 *  - segAABB / aabbOverlap : helpers for spatial filtering
 */

#include <algorithm>
#include <cmath>
#include <vector>

// ─── 2-D point ────────────────────────────────────────────────────────────────

struct Point {
    double x, y;
};

// ─── Axis-aligned bounding box ────────────────────────────────────────────────

struct AABB {
    double minx, miny, maxx, maxy;
};

/// Bounding box of a segment a→b.
inline AABB segAABB(const Point& a, const Point& b) {
    return { std::min(a.x, b.x), std::min(a.y, b.y),
             std::max(a.x, b.x), std::max(a.y, b.y) };
}

/// True if two AABBs overlap (including touching edges).
inline bool aabbOverlap(const AABB& a, const AABB& b) {
    return a.minx <= b.maxx && a.maxx >= b.minx &&
           a.miny <= b.maxy && a.maxy >= b.miny;
}

// ─── Triangle / area helpers ──────────────────────────────────────────────────

/// Signed area of triangle (a, b, c).  Positive ↔ CCW orientation.
inline double triArea(const Point& a, const Point& b, const Point& c) {
    return 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

/// Shoelace contribution of the directed edge p→q.
/// The full ring area = 0.5 * sum of shoelaceEdge over all consecutive pairs.
inline double shoelaceEdge(const Point& p, const Point& q) {
    return p.x * q.y - q.x * p.y;
}

/// Shoelace signed area of a closed polygon ring (positive = CCW).
inline double signedArea(const std::vector<Point>& pts) {
    double s = 0.0;
    int n = static_cast<int>(pts.size());
    for (int i = 0; i < n; ++i) {
        s += shoelaceEdge(pts[i], pts[(i + 1) % n]);
    }
    return 0.5 * s;
}

// ─── Segment–segment intersection ─────────────────────────────────────────────

/// Returns true if segments (p1,p2) and (p3,p4) *properly* intersect,
/// i.e. they cross strictly in their interiors (not merely touch at endpoints).
inline bool segmentsIntersect(const Point& p1, const Point& p2,
                               const Point& p3, const Point& p4) {
    auto cross2d = [](double ax, double ay, double bx, double by) {
        return ax * by - ay * bx;
    };

    double d1x = p2.x - p1.x, d1y = p2.y - p1.y;
    double d2x = p4.x - p3.x, d2y = p4.y - p3.y;
    double denom = cross2d(d1x, d1y, d2x, d2y);
    if (std::abs(denom) < 1e-15) return false; // parallel / collinear

    double dx = p3.x - p1.x, dy = p3.y - p1.y;
    double t = cross2d(dx, dy, d2x, d2y) / denom;
    double u = cross2d(dx, dy, d1x, d1y) / denom;

    constexpr double EPS = 1e-10;
    return (t > EPS && t < 1.0 - EPS && u > EPS && u < 1.0 - EPS);
}
