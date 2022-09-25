#include "Image.h"
#include "cs225/PNG.h"
#include <cmath>

using namespace cs225;
using namespace std;
void Image::lighten() {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.l += 0.1;
            if (to_change.l > 1.0) {to_change.l = 1.0;}
            if (to_change.l < 0.0) {to_change.l = 0.0;}
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.l += amount;
            if (to_change.l > 1.0) {to_change.l = 1.0;}
            if (to_change.l < 0.0) {to_change.l = 0.0;}
        }
    }
}

void Image::darken() {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.l -= 0.1;
            if (to_change.l > 1.0) {to_change.l = 1.0;}
            if (to_change.l < 0.0) {to_change.l = 0.0;}
        }
    }
}
void Image::darken(double amount) {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.l -= amount;
            if (to_change.l > 1.0) {to_change.l = 1.0;}
            if (to_change.l < 0.0) {to_change.l = 0.0;}
        }
    }
}
void Image::rotateColor	(double degrees) {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.h += degrees;
            while (to_change.h > 360) {to_change.h -= 360;}
            while (to_change.h < 0.0) {to_change.h += 360;}
        }
    }
}	

void Image::saturate() {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.s += 0.1;
            if (to_change.s > 1.0) {to_change.s = 1.0;}
            if (to_change.s < 0.0) {to_change.s = 0.0;}
        }
    }
}
void Image::saturate(double amount) {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.s += amount;
            if (to_change.s > 1.0) {to_change.s = 1.0;}
            if (to_change.s < 0.0) {to_change.s = 0.0;}
        }
    }
}
void Image::desaturate() {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.s -= 0.1;
            if (to_change.s > 1.0) {to_change.s = 1.0;}
            if (to_change.s < 0.0) {to_change.s = 0.0;}
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.s -= amount;
            if (to_change.s > 1.0) {to_change.s = 1.0;}
            if (to_change.s < 0.0) {to_change.s = 0.0;}
        }
    }
}
void Image::grayscale() {
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
            to_change.s = 0.0;
        }
    }
}
void Image::scale(double factor) {
    if (factor == 1.0) {
        return;
    }
    int new_width = factor * this->width();
    int new_height = factor * this->height();
    Image to_scale = Image(*this);
    resize(new_width,new_height);
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& ori_pixel = to_scale.getPixel(x/factor,y/factor);
            HSLAPixel& cur_pixel = getPixel(x,y);
            cur_pixel = ori_pixel;
        }
    }
}
void Image::scale(unsigned w,unsigned h) {
    Image to_scale = Image(*this);
    double fac_x = double(w)/width();
    double fac_y = double(h)/height();
    double fac_m = min(fac_x,fac_y);
    resize(fac_m*width(),fac_m*height());
    for (unsigned int y  = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& ori_pixel = to_scale.getPixel(double(x)/fac_m,double(y)/fac_m);
            HSLAPixel& cur_pixel = getPixel(x,y);
            cur_pixel = ori_pixel;
        }
    }
}

void Image::illinify() {

    for (unsigned int y = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            HSLAPixel& to_change = getPixel(x,y);
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