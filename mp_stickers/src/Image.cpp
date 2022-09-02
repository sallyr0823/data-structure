#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>

using namespace cs225;
using namespace std;
void Image::ChangeOfHue(PNG* image_p) {
    int width = image_p->width();
    int height = image_p->height();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            HSLAPixel& to_change = image_p->getPixel(x,y);
            if (ToOrange(to_change)) {
                to_change.h = orange;
            } else {
                to_change.h = blue;
            }
        }
    }
};


bool Image::ToOrange(HSLAPixel& pixel_p) {
    double hue_p = pixel_p.h;
    double diff_orange = abs(hue_p - orange);
    double diff_blue = abs(hue_p - blue);
    if (diff_orange >= 180) {
        diff_orange -= 180;
    }
    if (diff_blue >= 180) {
        diff_blue -= 180;
    }
    return (diff_orange < diff_blue);
};