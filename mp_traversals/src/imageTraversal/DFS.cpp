#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
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
  /** @todo [Part 1] */
  p_ = png;
  start_ = start;
  tol_ = tolerance;
  s_.push(start);
  //initialize visit vector
  visit_.resize(p_.width());
  for (unsigned i = 0; i < visit_.size(); i++) {
    visit_[i].resize(p_.height());
      for (unsigned j = 0; j < visit_[i].size(); j++) {
        visit_[i][j] = false;
      }
  }
  visit_[start_.x][start_.y] = true;

}
PNG* DFS::getPNG() {
  return &p_;
}

double DFS::getTol() {
  return tol_;
}


/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* dfs = new DFS(p_,start_,tol_);
  ImageTraversal::Iterator it = ImageTraversal::Iterator(dfs,start_);
  return it;
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
  /** @todo [Part 1] */
  s_.push(point);
  
}
void DFS::setVisited(Point input) {
  visit_[input.x][input.y] = true;
}

bool DFS::isVisited(Point input) {
  return (visit_[input.x][input.y]);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point p = s_.top();
  s_.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return s_.empty();
}
