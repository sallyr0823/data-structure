#pragma once

#include "ColorPicker.h"
#include "cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(double alpha);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel grey;
  HSLAPixel white;
  HSLAPixel black;
  HSLAPixel silver;
  double a;


};
