#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : trav(),flag_(true){
  /** @todo [Part 1] */

}
ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start) {
  trav = traversal;
  start_ = start;
  curr_ = trav -> peek();
  flag_ = false;
}

bool ImageTraversal::Iterator::isValid(const Point& input) {
  PNG* p = trav -> getPNG();
  double t = trav -> getTol();
  if (input.x >= p -> width() || input.x < 0) {
    return false;
  }
  if (input.y >= p -> height() || input.y < 0) {
    return false;
  }
  if (calculateDelta(p -> getPixel(input.x,input.y),p -> getPixel(start_.x,start_.y)) < trav -> getTol()){
    return true;
  } 
  return false;
}
// To whom it may concern:
// I refer to AMA slides when doing this MP
// There may be possibility that other students share similar logic
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  curr_ = trav -> pop();

  Point right,left,below,above;
  right = Point(curr_.x+1,curr_.y);
  left = Point(curr_.x-1,curr_.y);
  above = Point(curr_.x,curr_.y-1);
  below = Point(curr_.x,curr_.y+1);
  if(isValid(right)) {trav -> add(right);} //trav-> setVisited(right);}
  if(isValid(below)) {trav -> add(below);} //trav -> setVisited(below);}
  if(isValid(left)) {trav -> add(left);} //trav -> setVisited(left);}
  if(isValid(above)) {trav -> add(above);} //trav -> setVisited(above);}
  trav -> setVisited(curr_);
  while ( !(trav->empty()) && trav -> isVisited(trav -> peek())) {
  		trav->pop();
  }
  if (trav->empty()) {
    flag_ = true;
    return *this;
  }
  curr_ = trav -> peek();
  return *this;

  
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
  
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->flag_ == other.flag_);
}

