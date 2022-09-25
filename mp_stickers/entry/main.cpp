#include "../src/Image.h"
#include "../src/StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../tests/alma.png");
  Image i;    i.readFromFile("../tests/i.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);

  Image output_e = sheet.render();
  output_e.scale(0.5);
  output_e.writeToFile("../myImage.png");


  

  return 0;
}
