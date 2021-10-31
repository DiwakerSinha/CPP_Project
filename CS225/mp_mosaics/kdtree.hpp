/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <algorithm>
#include <utility>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> &first,
                                const Point<Dim> &second, int curDim) const {
  /**
   * @todo Implement this function!
   */
  if (curDim >= Dim) {
    return false;
  }

  if (first[curDim] < second[curDim]) {
    return true;
  } else if (first[curDim] > second[curDim]) {
    return false;
  } else if (first[curDim] == second[curDim]) {
    return first < second;
  }

  return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> &target,
                                const Point<Dim> &currentBest,
                                const Point<Dim> &potential) const {

  /**
   * @todo Implement this function!
   */
  double current_dist = 0.0;
  double potential_dist = 0.0;

  for (int i = 0; i < Dim; i++) {
    current_dist += squared(currentBest[i] - target[i]);
    potential_dist += squared(target[i] - potential[i]);
  }

  if (potential_dist < current_dist) {
    return true;
  } else if (potential_dist > current_dist) {
    return false;
  } else if (potential_dist == current_dist) {
    return potential < currentBest;
  }

  return false;
}

template <int Dim> 
double KDTree<Dim>::squared(const double value) const {
  return value * value;
}

template <int Dim> 
KDTree<Dim>::KDTree(const vector<Point<Dim>> &newPoints) {
  /**
   * @todo Implement this function!
   */
  if (newPoints.empty()) {
    root = NULL;
    size = 0;
  }

}

template <int Dim> 
KDTree<Dim>::KDTree(const KDTree<Dim> &other) {
  /**
   * @todo Implement this function!
   */
  copy(root, other.root);
}

template <int Dim>
const KDTree<Dim> &KDTree<Dim>::operator=(const KDTree<Dim> &rhs) {
  /**
   * @todo Implement this function!
   */
  if (this == &rhs) {
    return *this;
  }

  clear(root);

  copy(root, rhs.root);
  size = rhs.size;

  return *this;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode *subroot, KDTreeNode *other_subroot) {

  if (other_subroot == NULL) {
    return;
  }

  subroot = new KDTreeNode(other_subroot->point);

  copy(subroot->left, other_subroot->left);
  copy(subroot->right, other_subroot->right);
}

template <int Dim> KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim> 
void KDTree<Dim>::clear(KDTreeNode *subroot) {

  if (subroot == NULL) {
    return;
  }

  clear(subroot->left);
  clear(subroot->right);

  delete subroot;
  subroot = NULL;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &query) const {
  /**
   * @todo Implement this function!
   */
  return query;
}
