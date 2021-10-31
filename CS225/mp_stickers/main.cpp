#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image space;
  Image carleft;
  Image carright;
  Image explosion;
  
  space.readFromFile("space.png");
  carleft.readFromFile("carleft.png");
  carright.readFromFile("carright.png");
  explosion.readFromFile("explosion.png");
  
  space.scale(10.0);
  carleft.scale(5.0);
  carright.scale(2.0);
  
  StickerSheet sheet(space, 4);
  sheet.addSticker(explosion, 750, 100);
  sheet.addSticker(carleft, 250, 650);
  sheet.addSticker(carright, 1500, 600);

  
  Image output = sheet.render();
  output.writeToFile("myImage.png");
  
  return 0;
}
