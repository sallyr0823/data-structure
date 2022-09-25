#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include <cmath>
using namespace cs225;
using namespace std;


StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    cap_ = max;
    base_ =picture;
    sheet_ = new Image* [max];
    x_coord_ = new unsigned[max];
    y_coord_ = new unsigned[max];
    for (unsigned i = 0 ;i < max ; i++) {
        sheet_[i] = nullptr;
    }

}

StickerSheet::~StickerSheet () {
    Clear();
}
void StickerSheet::Clear() {
    delete[] sheet_;
    sheet_ = nullptr;
    delete[] x_coord_;
    x_coord_ = nullptr;
    delete[] y_coord_;
    y_coord_ = nullptr;

}
const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }
    cap_ = other.cap_;
    base_ = other.base_;
    sheet_ = new Image*[cap_];
    x_coord_ = new unsigned[cap_];
    y_coord_ = new unsigned[cap_];
    for (unsigned i = 0; i < cap_ ; i++) {
        if(other.sheet_[i] != nullptr) {
            sheet_[i] = new Image(*other.sheet_[i]);
        } else {
            sheet_[i] = nullptr;
        }
        x_coord_[i] = other.x_coord_[i];
        y_coord_[i] = other.y_coord_[i];
    }
    return *this;
}
StickerSheet::StickerSheet(const StickerSheet& other) {
    cap_ = other.cap_;
    base_ = other.base_;
    sheet_ = new Image*[cap_]();
    x_coord_ = new unsigned[cap_];
    y_coord_ = new unsigned[cap_];
    for (unsigned i = 0; i < cap_ ; i++) {
        if(other.sheet_[i] != nullptr) {
            sheet_[i] = other.sheet_[i];
        } else {
            sheet_[i] = nullptr;
        }
        x_coord_[i] = other.x_coord_[i];
        y_coord_[i] = other.y_coord_[i];
    }
}	
void StickerSheet::changeMaxStickers (unsigned max) {
    if (max == cap_) {
        return;
    }
    Image **temp = new Image*[max];
    unsigned *x_temp_ = new unsigned[max];
    unsigned *y_temp_ = new unsigned[max];
    if (max > cap_) {
        for (unsigned i = 0; i < cap_; i++) {
            temp[i] = sheet_[i];
            x_temp_[i] = x_coord_[i];
            y_temp_[i] = y_coord_[i];
        }
        for (unsigned i = cap_; i < max; i++) {
            temp[i] = nullptr;
        }
    }
    if (max < cap_) {
        for (unsigned i = 0; i < max; i++) {
            temp[i] = sheet_[i];
            x_temp_[i] = x_coord_[i];
            y_temp_[i] = y_coord_[i];
        }
    }
    Clear();
    sheet_ = temp;
    x_coord_ = x_temp_;
    y_coord_ = y_temp_;
    cap_ = max;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    for (unsigned i = 0; i < cap_; i++) {
        if (sheet_[i] == nullptr) {
            sheet_[i] =  new Image(sticker);
            x_coord_[i] = x;
            y_coord_[i] = y;
            return i;
        }
    }
    return -1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index >= cap_) {
        return false;
    }
    if (sheet_[index] == nullptr) {
        return false;
    }
    x_coord_[index] = x;
    y_coord_[index] = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index) {
    if (index >= cap_ || sheet_[index] == nullptr) {
        return;
    }
    //delete sheet_[index];
    sheet_[index] = nullptr;
    x_coord_[index] = 0;
    y_coord_[index] = 0;
        /*unsigned i = index;
        while(sheet_[i+1] != nullptr) {
            sheet_[i] = sheet_[i+1];
            x_coord_[i] = x_coord_[i+1];
            y_coord_[i] = y_coord_[i+1];
            i++;
        }
        delete sheet_[i];
        sheet_[i] = nullptr;
        x_coord_[i] = 0;
        y_coord_[i] = 0;*/
}
Image* StickerSheet::getSticker (unsigned index) {
    if (index < 0 || index >= cap_ || sheet_[index] == nullptr) {
        return nullptr;
    }
    return sheet_[index];
}

Image StickerSheet::render() const {
    //find the bound
    //unsigned int max_x = base_ -> width();
    unsigned max_x = base_.width();
    unsigned max_y=  base_.height();
    //unsigned int max_y = base_ -> height();
    for (unsigned i = 0 ; i < cap_; i++) {
        if (sheet_[i] !=  nullptr) {
            max_x = max(max_x,x_coord_[i] + sheet_[i] -> width());
            max_y = max(max_y,y_coord_[i] + sheet_[i] -> height());
        }
    }
    
    Image to_render = Image(base_);
    to_render.resize(max_x,max_y);
    to_render.scale(max_x,max_y);

    for (unsigned int i = 0 ; i < cap_ ; i++) {
        if(sheet_[i] != nullptr) {
            for (unsigned w = 0; w < sheet_[i] -> width(); w++) {
                for (unsigned h = 0; h < sheet_[i] -> height(); h++) {
                    //HSLAPixel & rend_p = to_render.getPixel(x_coord_[i] + w, y_coord_[i] + h);
                    HSLAPixel & sheet_p = sheet_[i]-> getPixel(w,h);
                    if (sheet_p.a != 0) {
                        to_render.getPixel(x_coord_[i] + w, y_coord_[i] + h) = sheet_p;
                    }
                }
            }
        }
    }
    
    return to_render;
}

