#include <iostream>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using cs225::HSLAPixel;
using cs225::PNG;
using namespace cs225;

void Image::lighten() {
  /// Increasing luminance by 0.1 while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.l <= 0.9) {
          pixel.l = pixel.l + 0.1;
      } else {
          pixel.l = 1.0;
      }
      
    }
  }
}

void Image::lighten(double amount) {
  /// Increasing luminance by amount while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.l + amount <= 1.0) {
          pixel.l = pixel.l + amount;
      } else {
          pixel.l = 1.0;
      }
      
    }
  }
}


void Image::darken() {
  /// Decreasing luminance by 0.1 while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.l >= 0.1) {
          pixel.l = pixel.l - 0.1;
      } else {
          pixel.l = 0.0;
      }
      
    }
  }
}


void Image::darken(double amount) {
  /// Decreasing luminance by amount while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.l - amount >= 0.0) {
          pixel.l = pixel.l - amount;
      } else {
          pixel.l = 0.0;
      }
      
    }
  }
}


void Image::saturate() {
  /// Increasing saturation by 0.1 while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.s <= 0.9) {
          pixel.s = pixel.s + 0.1;
      } else {
          pixel.s = 1.0;
      }
      
    }
  }
}


void Image::saturate(double amount) {
  /// Increasing luminance by amount while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.s + amount <= 1.0) {
          pixel.s = pixel.s + amount;
      } else {
          pixel.s = 1.0;
      }
      
    }
  }
}



void Image::desaturate() {
  /// Decreasing saturation by 0.1 while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.s >= 0.1) {
          pixel.s = pixel.s - 0.1;
      } else {
          pixel.s = 0.0;
      }
      
    }
  }
}


void Image::desaturate(double amount) {
  /// Decreasing luminance by amount while keeping within [0,1]
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      if (pixel.s - amount >= 0.0) {
          pixel.s = pixel.s - amount;
      } else {
          pixel.s = 0.0;
      }
      
    }
  }
}


void Image::grayscale() {
  /// This function makes the image grayscale
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}


void Image::rotateColor(double degrees) {
  /// To rotate the hue
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      
      if (degrees >= 0) { //positive shift
          if((pixel.h + degrees) >= 360) {
              pixel.h = degrees - (360 - pixel.h);
          } else {
              pixel.h = pixel.h + degrees;
          }
      } else { //negative shift
            if (pixel.h + degrees <=0) {
                pixel.h = 360 + (degrees +pixel.h);
            } else {
                pixel.h = pixel.h + degrees;
            }
      }
    }
  }
}



void Image::illinify() {

  /// nested for loops to go through the entire image
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      // to obtin the pixels
      HSLAPixel & pixel = this->getPixel(x, y);
      
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
}

void Image::scale(double factor){
  unsigned int scaled_width = this->width() * factor;
  unsigned int scaled_height = this->height() * factor;
  
  //Temporary image scaled by given factor
  PNG* scaled_image = new PNG(scaled_width, scaled_height);
  
  /// nested for loops to go through the entire image
  for (unsigned x = 0; x < scaled_width; x++) {
    for (unsigned y = 0; y < scaled_height; y++) {
      unsigned temp_x = x/factor + 0.5;
      unsigned temp_y = y/factor + 0.5;
      if (temp_x == this->width()) {
        temp_x = this->width() - 1;
      }
      if (temp_y == this->height()) {
        temp_y = this->height() - 1;
      }
      HSLAPixel & pixel1 = this->getPixel(temp_x, temp_y);
      HSLAPixel & pixel2 = scaled_image->getPixel(x, y);
      
      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      pixel2 = pixel1;
    }
  }
  
  this->resize(scaled_width, scaled_height);
  for (unsigned x = 0; x < scaled_width; x++) {
    for (unsigned y = 0; y < scaled_height; y++) {
      HSLAPixel & pixel1 = this->getPixel(x, y);
      //Finding corresponding x and y pixels to assign to new image
      HSLAPixel & pixel2 = scaled_image->getPixel(x, y);
      pixel1 = pixel2;
    }
  }
  delete scaled_image;
  scaled_image = NULL;
}



void Image::scale(unsigned w, unsigned h){
  //Again creating new image, but this time with the given dimensions.
  PNG* scaled_image = new PNG(w, h);
  
  /// nested for loops to go through the entire image
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      
      unsigned temp_x = x/w + 0.5;
      unsigned temp_y = y/h + 0.5;
      if (temp_x == this->width()) {
        temp_x = this->width() - 1;
      }
      if (temp_y == this->height()) {
        temp_y = this->height() - 1;
      }
      HSLAPixel & pixel1 = this->getPixel(temp_x,temp_y);
      HSLAPixel & pixel2 = scaled_image->getPixel(x, y);
      
      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      
      
      //Now to correlate and assign the pixels from the original image to the newer image
      pixel2 = pixel1;
    }
  }
  
  //Modifying the original image
  this->resize(w, h);
  
  /// nested for loops to go through the entire image
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      
      HSLAPixel & pixel1 = this->getPixel(x, y);
      //Finding corresponding x and y pixels to assign to new image
      HSLAPixel & pixel2 = scaled_image->getPixel(x, y);
      pixel1 = pixel2;
    }
  }
  delete scaled_image;
  scaled_image = NULL;
}