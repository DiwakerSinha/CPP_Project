/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {


HSLAPixel::HSLAPixel() {
  //here we take default values
  a=1;
  l=1;
  h=0;
  s=1.0;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
  //here we copied the 3/4 parameters given and assumed the picture to be opaque.
  h=hue;
  s=saturation;
  l=luminance;
  a=1.0;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
  //here we replaced all class parameters with the ones given in brackets.
  h=hue;
  s=saturation;
  l=luminance;
  a=alpha;
}

}
