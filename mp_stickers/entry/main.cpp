#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image addp1;
  addp1.readFromFile("tests/i.png");
  
  Image alma;
  alma.readFromFile("tests/alma.png");


  StickerSheet sheet(alma, 5);

  

  return 0;
}
