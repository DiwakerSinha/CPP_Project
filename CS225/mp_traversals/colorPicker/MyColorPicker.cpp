#include <random>

#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"


using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(158, 0.8, 0.5);
  double random_generator = rand() * 360;
  pixel.h = (unsigned int)(pixel.h * random_generator) % 360;
  return pixel;
}
