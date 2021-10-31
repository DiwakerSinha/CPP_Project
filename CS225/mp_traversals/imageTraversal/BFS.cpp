#include <cmath>
#include <iterator>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "BFS.h"
#include "ImageTraversal.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger
 * than tolerance) with the start point, it will not be included in this BFS
 */
BFS::BFS(const PNG &png, const Point &start, double tolerance) {
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  points_.push_back(start_);

  for (size_t i = 0; i < png_.width(); i++) {
    vector<bool> to_add;
    for (size_t j = 0; j < png_.height(); j++) {
      to_add.push_back(0);
    }
    visited.push_back(to_add);
  }

  //visited[start_.x][start_.y] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * bfs = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(bfs, start_, png_, tolerance_, visited);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point &point) {
  /** @todo [Part 1] */
  points_.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if (points_.empty()) {
    return Point(-1, -1);
  } 
  Point temp = points_.front();
  points_.pop_front();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if (points_.empty()) {
    return Point(-1, -1);
  }
  return points_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if (points_.empty()) {
    return 1;
  } 
  return 0; 
}