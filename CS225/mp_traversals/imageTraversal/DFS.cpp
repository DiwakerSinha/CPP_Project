#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) { 
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  
  for (size_t i = 0; i < png_.width(); i++) {
    vector <bool> to_add;
    for (size_t j = 0; j < png_.height(); j++) {
      to_add.push_back(0);
    }
    visited.push_back(to_add);
  }

  // if (visited.size() != 0) {
  //   visited[start_.x][start_.y] = true;
  // }

  points_.push_back(start_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * dfs = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(dfs, start_, png_, tolerance_, visited);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  points_.push_back(point);
  /** @todo [Part 1] */
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if (points_.empty()) {
    return Point(-1, -1);
  }
  Point temp = points_.back();
  points_.pop_back();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (points_.empty()) {
    return Point(-1, -1);
  }
  return points_.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if (points_.empty()) {
    return 1;
  } 
    return 0;
}

