/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#ifndef IMAGE_H
#define IMAGE_H
#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

/* What to claim here:
1.read from file;
2.lighten;
3.write to file;
4.saturate;
5.scale;
*/
class Image{
    public: 
        void ChangeOfHue(cs225::PNG* image_p);
        bool ToOrange(cs225::HSLAPixel& pixel_p);
    private:
        const double orange = 11;
        const double blue = 216;

};
#endif