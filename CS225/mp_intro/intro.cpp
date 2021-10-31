#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>
#include <cmath>
#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  //reading and creating a temp output png
  cs225::PNG inp;
  inp.readFromFile(inputFile);
  cs225::PNG out;
  out = cs225::PNG(inp);
  unsigned width = inp.width();
  unsigned height = inp.height();
  
  // loop to go through all pixels
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      cs225::HSLAPixel & pixelinput = inp.getPixel(x, y); //
      cs225::HSLAPixel & pixeloutput = out.getPixel(width - x - 1,height - y - 1); //
      pixeloutput = pixelinput;
      // replacing output pixel with desired pixel from input png
    }
  }
  
  out.writeToFile(outputFile);
  // outputting req. pictures
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  
  // Art to create a checkerboard pattern

  int hue_primary = 11; // for hozizontal stripes
  int hue_secondary = 216; // for vertical stripes
  
  // looping through pixels
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      
      // to create a gradient for 50 pixels
      if (y > 0 && (y % 50 == 0)) {
        hue_primary += 1;
      }
      
      // incase the hue goes over 360
      if (hue_primary > 360) {
        hue_primary = hue_primary % 360;
      }
      // setting values for hsla
      pixel.h = hue_primary;
      pixel.s = 0.8;
      pixel.l = 0.5;
      pixel.a = 0.9999;
      
    }
  }
  
  // same as the horizontal pattern with more transparency
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < (height); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(y, x);
      if (y > 0 && (y % 50 == 0)) {
        hue_secondary += 1;
      }
      if (hue_secondary > 360) {
        hue_secondary = hue_secondary % 360;
      }
      pixel.h = hue_secondary;
      pixel.s = 0.8;
      pixel.l = 0.5;
      pixel.a = 0.4; // reduced value to allow more transparency
      
    }
  }

  return png; // returning art
}
