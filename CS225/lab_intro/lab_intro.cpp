/**
 * @file lab_intro.cpp
 * Implementations of image manipulation functions.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using cs225::HSLAPixel;
using cs225::PNG;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  /// nested for loops to go through the entire image
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      //getting pixel at x,y
      HSLAPixel & pixel = image.getPixel(x, y);
      
      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      // distance from the center pixel for x and y coordinates
      int x_dis = ((x-centerX)<0)?(centerX-x):(x-centerX);
      int y_dis = ((y-centerY)<0)?(centerY-y):(y-centerY);
      //calculating euclidean distance from the center
      double euc_dist = (sqrt((x_dis*x_dis) + (y_dis*y_dis)));
      
      
      double decrease = 1 - (0.005 * euc_dist); //calculating the decrease factor
      if (decrease <= 0.2) {
        decrease = 0.2; //keeps a max decrease of 80%
      }
      // to reduce luminance
      pixel.l = pixel.l * decrease;
       
    }
  }
  
  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {

  /// nested for loops to go through the entire image
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      // to obtin the pixels
      HSLAPixel & pixel = image.getPixel(x, y);
      
      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      
      //Since the Illini Orange has a hue of 11, and Illini Blue has hue 216. that means that the
      //Finding the points which lie in between those are at the points 293.5 and 113.5. 
      if (pixel.h>=293.5||pixel.h<113.5)
        pixel.h=11;
      else
        pixel.h=216;
      
    }
  }
  
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

  unsigned int imgwidth, imgheight;
  // to find the larger of the width and height of the two inputted pictures.
  imgwidth=((firstImage.width()>secondImage.width())?firstImage.width():secondImage.width());
  imgheight=((firstImage.height()>secondImage.height())?firstImage.height():secondImage.height());
  // nested loop to go through the image 
  for (unsigned x = 0; x < imgwidth; x++) {
    for (unsigned y = 0; y < imgheight; y++) {
      //obtaining pixels for both images
      HSLAPixel & pixel1 = firstImage.getPixel(x, y);
      HSLAPixel & pixel2 = secondImage.getPixel(x, y);
      
      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      if (pixel2.l==1) // checking if luminance is at a 100%
        pixel1.l = (pixel1.l+0.2>1.0)?1.0:pixel1.l+0.2; //changing luminance of original picture as per the given condition
    }
  }
  return firstImage;
}
