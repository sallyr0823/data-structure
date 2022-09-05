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
using namespace cs225;
class Image : public PNG{
    public: 
        void lighten();
        void lighten(double amount);
        void rotateColor(double degrees);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale ();
        void scale(double factor);
        void scale(unsigned w,unsigned h); 
        void illinify();
    private:
        const double orange = 11;
        const double blue = 216;
        bool ToOrange(HSLAPixel& pixel_p);


};
#endif