#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(double alpha){
  /* @todo [Part 3] */
  a = alpha;
  grey = HSLAPixel(0,0,0.5,a);
  black = HSLAPixel(0,0,0,a);
  silver = HSLAPixel(0,0,0.75,a);
  white = HSLAPixel(0,0,1,a);
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  if (x % 2 == 1 && y % 2 == 1) {
    return black;
  } else if (x % 2 == 0 && y % 2 == 1) {
    return white;
  } else if (x % 2 == 1 && y % 2 == 1) {
    return grey;
  }
  return silver;  
}