#include <iostream>
#include <cassert>
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG png;
  png.readFromFile("/workspaces/CS225-2022/cs225-fa22/mp_traversals/han.png");
  
  FloodFilledImage image(png);
  BFS bfs(png, Point(20, 60), 0.05);
  DFS dfs(png, Point(80, 80), 0.05);
  RainbowColorPicker rainbow(0.05);
  MyColorPicker mine(0.9);
  image.addFloodFill( bfs, rainbow );
  image.addFloodFill( bfs,  mine);
  image.addFloodFill( dfs,  mine);
  image.addFloodFill( bfs,  rainbow);
  image.addFloodFill( bfs,  mine);
  image.addFloodFill( dfs,  rainbow);
  image.addFloodFill( dfs,  mine);


  Animation animation = image.animate(1000);


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  //std::cout << "Files written to lantern-rainbow-bfs-* for debugging." << std::endl;
  
  /*PNG png(4, 4);
  HSLAPixel blackPixel(180, 1, 0);
  
  for (unsigned i = 0; i < 4; i++) {
    png.getPixel(i, 0) = blackPixel;
    png.getPixel(0, i) = blackPixel;
    png.getPixel(i, 3) = blackPixel;
    png.getPixel(3, i) = blackPixel;
  }
  Point startPoint(1, 1);
  
  DFS dfs(png, startPoint, 0.2);
  ImageTraversal::Iterator it = dfs.begin();
  assert( *it == startPoint);
  ++it;
  assert( *it == Point(1, 2) );*/
}
