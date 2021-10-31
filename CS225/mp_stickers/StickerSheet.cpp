#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    base_picture = picture;
    max_images = max;
    current_images = 0;
    image_pointer_array = new Image* [max_images];
    for (size_t i = 0; i < max_images; i++) {
      image_pointer_array[i] = NULL;
    }
    x_coordinate = new unsigned int [max_images];
    y_coordinate = new unsigned int [max_images];
}

StickerSheet::~StickerSheet() {
  delete[] image_pointer_array;
  delete[] x_coordinate;
  delete[] y_coordinate;
  // base_picture = NULL;
  //max_images;
  //current_images;
  
}


StickerSheet::StickerSheet(const StickerSheet &other) {
  
  base_picture = other.base_picture;
  max_images = other.max_images;
  current_images = other.current_images;
  image_pointer_array = new Image* [max_images];
  x_coordinate = new unsigned int [max_images];
  y_coordinate = new unsigned int [max_images];

  for (size_t i = 0; i < max_images; i++){
    //Check this line later
    image_pointer_array[i] = other.image_pointer_array[i];
    x_coordinate[i] = other.x_coordinate[i];
    y_coordinate[i] = other.y_coordinate[i];
  }
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
  if ((int)current_images == (int)(max_images) - 1) {
    return -1;
  }
  if (image_pointer_array[current_images] == NULL) {
    image_pointer_array[current_images] = new Image(sticker);
  } else {
    *image_pointer_array[current_images] = sticker;
  }
  x_coordinate[current_images] = x;
  y_coordinate[current_images] = y;
  current_images++;
  return current_images - 1;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  
  if (max != max_images) {
    
    if (max < max_images) {
      for (size_t i = max; i < max_images; i++) {
        image_pointer_array[i] = NULL;
        x_coordinate[i] = 0;
        y_coordinate[i] = 0;
      }
      max_images = max;
      current_images = max - 1;
      return;
    } 
    
    Image** copy = new Image*[max];
    for (size_t i = 0; i < max; i++) {
      copy[i] = NULL;
    }
    unsigned int* x_copy = new unsigned int[max];
    unsigned int* y_copy = new unsigned int[max];

    for (size_t i = 0; i < max_images; i++) {
      copy[i] = new Image();
      *(copy[i]) = *(image_pointer_array[i]);
      x_copy[i] = x_coordinate[i];
      y_copy[i] = y_coordinate[i];
    }
    
    max_images = max;
    
    delete[] image_pointer_array;
    image_pointer_array = copy;
    delete[] copy;
    copy = NULL;
    
    delete[] x_coordinate;
    x_coordinate = x_copy;
    delete[] x_copy;
    x_copy = NULL;
    
    delete[] y_coordinate;
    y_coordinate = y_copy;
    delete[] y_copy;
    y_copy = NULL;
  }
}


Image* StickerSheet::getSticker (unsigned index) {
  if ((int)index > current_images) {
    return NULL;
  }
  return (image_pointer_array[index]);
}


const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
  delete[] image_pointer_array;
  delete[] x_coordinate;
  delete[] y_coordinate;
  base_picture = other.base_picture;
  max_images = other.max_images;
  current_images = other.current_images;
  image_pointer_array = new Image* [max_images];
  x_coordinate = new unsigned int [max_images];
  y_coordinate = new unsigned int [max_images];
  
  for (size_t i = 0; i < max_images; i++){
    //Check this line later
    image_pointer_array[i] = other.image_pointer_array[i];
    x_coordinate[i] = other.x_coordinate[i];
    y_coordinate[i] = other.y_coordinate[i];
  }
  return *this;
}


void StickerSheet::removeSticker(unsigned index) {
  if ((int)index <= current_images) {
    image_pointer_array[index] = NULL;
    x_coordinate[index] = 0;
    y_coordinate[index] = 0;
    
    for (size_t i = index; i < max_images - 1; i++) {
      *(image_pointer_array[i]) = *(image_pointer_array[i + 1]);
      x_coordinate[i] = x_coordinate[i + 1];
      y_coordinate[i] = y_coordinate[i + 1];
    }
    
    image_pointer_array[max_images - 1] = NULL;
    x_coordinate[max_images - 1] = 0;
    y_coordinate[max_images - 1] = 0;
  }
}


Image StickerSheet::render() const{
  
  unsigned max_width = base_picture.width();
  unsigned max_height = base_picture.height();
  
  for (size_t i = 0; i < max_images; i++){
    if(image_pointer_array[i] == NULL){ 
      continue;
    }
    if(x_coordinate[i] + (image_pointer_array[i]->width()) > max_width){
      max_width = x_coordinate[i] + (image_pointer_array[i]->width());
    }
    if(y_coordinate[i] + (image_pointer_array[i]->height()) > max_height){
      max_height = y_coordinate[i] + (image_pointer_array[i]->height());
    }
  }
  
  Image combined = base_picture;
  combined.resize(max_width, max_height);
  
  
  for (size_t i = 0; i < max_images; i++){
    
    if (image_pointer_array[i] == NULL){ 
      continue;
    }
      
    for (size_t j = x_coordinate[i]; j < (x_coordinate[i] + (image_pointer_array[i]->width())); j++){
        
      for(size_t k = y_coordinate[i]; k < (y_coordinate[i] + (image_pointer_array[i]->height())); k++){
          
        if((image_pointer_array[i]->getPixel((j - x_coordinate[i]), (k - y_coordinate[i]))).a != 0){
            
          combined.getPixel(j, k) = image_pointer_array[i]->getPixel((j - x_coordinate[i]), (k - y_coordinate[i]));
            
        }
      }
    }
  }
  return combined;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index >= max_images || image_pointer_array[index] == NULL){
    return false;
  } else {
    x_coordinate[index] = x;
    y_coordinate[index] = y;
  }
  return true;
}
