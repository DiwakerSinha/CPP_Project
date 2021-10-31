/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
class HSLAPixel{
public:
  double h; //hues [0, 360)
  double l; //luminance [0,1]
  double s; //saturation [0,1]
  double a; //alpha [0,1]
  HSLAPixel(); //default constructor
  HSLAPixel(double hue, double saturation, double luminance); //constructor with 3/4 parameters, meant to produce a white opaque picture.
  HSLAPixel(double hue, double saturation, double luminance, double alpha); //constructor with all parameters given.
}; //end of class HSLAPixel
} //end of namespace cs225
