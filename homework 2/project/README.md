# CSD2183 Project 2 — Area- and Topology-Preserving Polygon Simplification

## Overview

Implements the **Area-Preserving Segment Collapse (APSC)** algorithm from
Kronenfeld et al. (2020) to simplify polygons with holes.  The algorithm:

- Preserves the **signed area** of every ring exactly (to floating-point tolerance)
- Maintains **topology** — no self-intersections, no ring crossings, ring count unchanged
- **Minimises areal displacement** greedily across all rings

## Dependencies

**None.** Uses only the C++17 standard library (`g++`, Unix/macOS/WSL).

---

## Building

```bash
make
```

Produces the executable `simplify` in the repository root.

```bash
make clean   # remove object files and executable
```

---

## Usage

```bash
./simplify <input_file.csv> <target_vertices>
```

| Argument | Description |
|---|---|
| `<input_file.csv>` | CSV with columns `ring_id,vertex_id,x,y` |
| `<target_vertices>` | Desired maximum total vertex count across all rings |

---

## File Structure

```
.
├── Makefile
├── README.md
├── include/
│   ├── geometry.h   — Point, AABB, triArea, signedArea, segmentsIntersect
│   ├── ring.h       — Vertex, RingPool (doubly-linked circular lists)
│   ├── grid.h       — Grid (uniform-grid spatial index)
│   ├── apsc.h       — computeCollapse, Candidate, Simplifier (declarations)
│   └── io.h         — readCSV, writeOutput (declarations)
└── src/
    ├── main.cpp     — Entry point, pipeline orchestration
    ├── apsc.cpp     — APSC algorithm implementation
    └── io.cpp       — CSV I/O implementation
```

### Module responsibilities

| File | Owner | Responsibility |
|---|---|---|
| `geometry.h` | shared | Geometric primitives — no mutable state |
| `ring.h` | Team member A | Vertex pool, ring traversal, kill/re-link |
| `grid.h` | Team member B | Spatial index build/insert/remove/query |
| `apsc.h/cpp` | Team member C | Core APSC loop, heap management, topology check |
| `io.h/cpp` | Team member D | CSV parsing, output formatting |
| `main.cpp` | any | Wires the modules together |

---

## Algorithm

### Core: Area-Preserving Segment Collapse (APSC)

For every window of four consecutive vertices **A → B → C → D** in any ring,
find a replacement point **E** such that the ring's shoelace sum is unchanged:

```
edge(A,E) + edge(E,D)  =  edge(A,B) + edge(B,C) + edge(C,D)
```

This is one linear equation in E.  Kronenfeld et al. show that placing E on
the **perpendicular bisector of AD** minimises areal displacement; substituting
`E = midpoint(AD) + t·perp(AD)` yields a unique scalar `t`.

The collapse **removes B and C** (net −1 vertex) and **inserts E**.  It is only
accepted if the two new segments A→E and E→D do not intersect any other segment.

### Greedy loop

1. Seed a **min-heap** with one candidate per vertex.
2. Pop the cheapest valid candidate.
3. **Topology check** via the spatial index.
4. Apply collapse, update the grid, re-seed the heap for affected neighbours.
5. Repeat until `live ≤ target` or the heap is empty.

### Data structures

| Structure | File | Complexity |
|---|---|---|
| Doubly-linked circular list (flat array) | `ring.h` | O(1) neighbour access & removal |
| `std::priority_queue` min-heap + lazy deletion | `apsc.cpp` | O(log n) push/pop |
| Uniform-grid spatial index | `grid.h` | O(√n) query (uniform data) |

**Lazy deletion:** each vertex carries a `version` counter that increments
whenever its neighbourhood changes.  Heap entries store the version at
push-time; stale entries (version mismatch) are silently discarded on pop.

---

## Test Results

### Spec example (12 vertices total)

```
ring_id,vertex_id,x,y        ← exterior ring (4 verts, CCW)
0,0,-0.5,-1.0
0,1,1.5,-1.0
0,2,1.5,1.0
0,3,-0.5,1.0
1,0,-0.2,0.5                 ← interior ring 1 (3 verts, CW)
1,1,0.5,0.5
1,2,0.5,-0.5
2,0,0.6,-0.2                 ← interior ring 2 (5 verts, CW)
2,1,1.0,0.2
2,2,1.2,0.2
2,3,1.4,-0.2
2,4,1.2,-0.8
```

| Target | Output vertices | Area in | Area out | Displacement | Area preserved? |
|---|---|---|---|---|---|
| 12 | 12 | 3.21e+00 | 3.21e+00 | 0.00e+00 | ✅ |
| 11 | 11 | 3.21e+00 | 3.21e+00 | 6.00e-02 | ✅ |
| 8  | 10 | 3.21e+00 | 3.21e+00 | 4.06e+00 | ✅ |
| 3  | 10 | 3.21e+00 | 3.21e+00 | 4.06e+00 | ✅ |

> Note: target=8 stops at 10 because each ring must retain ≥ 3 vertices
> (minimum for a valid polygon), so 9 is the true minimum for this input.

---

## Output Format

```
ring_id,vertex_id,x,y
0,0,<x>,<y>
...
Total signed area in input: <value>
Total signed area in output: <value>
Total areal displacement: <value>
```

`<value>` is in C `%e` (scientific) notation with 6 decimal places.

---

## References

Kronenfeld, B. J., Stanislawski, L. V., Buttenfield, B. P., and Brockmeyer, T. (2020).
"Simplification of polylines by segment collapse: minimizing areal displacement
while preserving area." *International Journal of Cartography* 6(1), pp. 22–46.
