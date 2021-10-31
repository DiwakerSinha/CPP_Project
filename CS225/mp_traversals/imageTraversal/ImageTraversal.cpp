#include <cmath>
#include <iostream>
#include <iterator>

#include "../Point.h"
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel &p1,
                                      const HSLAPixel &p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) {
    h = 360 - h;
  }
  h /= 360;

  return sqrt((h * h) + (s * s) + (l * l));
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  current = Point(-1, -1);
}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, Point start,
                                   PNG png, double tolerance,
                                   vector<vector<bool>> visited) {
  traversal_ = traversal;
  // current_ = start;
  png_ = png;
  tolerance_ = tolerance;
  current = start;

  for (size_t i = 0; i < visited.size(); i++) {
    vector<bool> to_add;
    for (size_t j = 0; j < visited.at(i).size(); j++) {
      to_add.push_back(visited[i][j]);
    }
    visited_.push_back(to_add);
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator &ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  current = traversal_->pop();

  Point left((unsigned)current.x - 1, (unsigned)current.y);
  Point right((unsigned)current.x + 1, current.y);
  Point up(current.x, (unsigned)current.y - 1);
  Point down(current.x, (unsigned)current.y + 1);

  HSLAPixel &pixel1 = png_.getPixel(current.x, current.y);

  if ((right.x < png_.width()) && (right.y < png_.height())) {
    HSLAPixel &pixel2 = png_.getPixel(right.x, left.y);
    if ((calculateDelta(pixel1, pixel2) < tolerance_) &&
        (!visited_[right.x][right.y])) {
      traversal_->add(right);
    }
  }

  if ((down.x < png_.width()) && (down.y < png_.height())) {
    HSLAPixel &pixel2 = png_.getPixel(down.x, down.y);
    if ((calculateDelta(pixel1, pixel2) < tolerance_) &&
        (!visited_[down.x][down.y])) {
      traversal_->add(down);
    }
  }

  if ((left.x < png_.width()) && (left.y < png_.height())) {
    HSLAPixel &pixel2 = png_.getPixel(left.x, left.y);
    if ((calculateDelta(pixel1, pixel2) < tolerance_) &&
        (!visited_[left.x][left.y])) {
      traversal_->add(left);
    }
  }

  if ((up.x < png_.width()) && (up.y < png_.height())) {
    HSLAPixel &pixel2 = png_.getPixel(up.x, up.y);
    if ((calculateDelta(pixel1, pixel2) < tolerance_) &&
        (!visited_.at(up.x).at(up.y))) {
      traversal_->add(up);
    }
  }

  visited_.at(current.x).at(current.y) = 1;
  current = traversal_->peek();

  while (!(traversal_->empty())) {
    if ((current.x != (unsigned)(-1) && current.y != (unsigned)(-1)) && visited_.at(current.x).at(current.y) == 1) {
      current = traversal_->pop();
      current = traversal_->peek();
    } else {
      break;
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::
operator!=(const ImageTraversal::Iterator &other) {
  // /** @todo [Part 1] */
  if (current == other.current) {
    return false;
  }
  return true;
}
