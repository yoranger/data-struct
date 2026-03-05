#ifndef IMAGE_SEGMENTATION_H
#define IMAGE_SEGMENTATION_H

#include <vector>

using namespace std;

// Compute the total weight of a Minimum Spanning Tree (MST) for a small
// grayscale image modelled as a 4-neighbour graph.
//
// - rows, cols: image dimensions
// - pixels: grayscale intensities in row-major order (size = rows * cols)
//
// Each pixel is a node. Two neighbouring pixels (up, down, left, right) are
// connected by an edge whose weight is the absolute difference in intensity
// between the two pixels. The function should:
//   1. Build this graph, then
//   2. Use an MST algorithm (Prim's or Kruskal's) to compute the MST, and
//   3. Return the total MST weight (sum of all edge weights in the MST).
int imageMSTCost(int rows, int cols, const vector<int> &pixels);

#endif  // IMAGE_SEGMENTATION_H

