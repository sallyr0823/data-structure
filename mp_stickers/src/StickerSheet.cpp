#include <StickerSheet.h>
#include "Image.h"
#include "cs225/PNG.h"
using namespace cs225;
using namespace std;


StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    cap_ = max;
    base_ = new Image(picture);
    stickers_ = new Sticker[max]();
}
StickerSheet::~StickerSheet () {
    delete base_;
    base_ = nullptr;
    for (unsigned i = 0 ; i < cap_ ; i++) {
        delete stickers_[i].image;
        stickers_[i].image = nullptr;
    }
    delete[] stickers_;
}
const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }
    cap_ = other.cap_;
    base_  = new Image(*other.base_);
    stickers_ = new Sticker[cap_]();
    for (unsigned i = 0; i < cap_; i++) {
        stickers_[i] = other.stickers_[i];
        stickers_[i].xcoord = other.stickers_[i].xcoord;
        stickers_[i].ycoord = other.stickers_[i].ycoord;
    }
    
    return *this;
}
StickerSheet::StickerSheet(const StickerSheet& other) {
    cap_ = other.cap_;
    base_ = new Image(*other.base_);
    stickers_ = new Sticker[cap_]();
    for (unsigned i = 0; i < cap_ ; i++) {
        if (other.stickers_[i].image != nullptr) {
            stickers_[i].image= new Image(*(other.stickers_[i].image));
            stickers_[i].xcoord = other.stickers_[i].xcoord;
            stickers_[i].ycoord = other.stickers_[i].ycoord;
        }
    }
}	
void StickerSheet::changeMaxStickers (unsigned max) {
    if (max > cap_) {
        cap_ = max;
    } else {
        for (unsigned i = max ; i < cap_; i++) {
            if (stickers_[i].image != nullptr) {
                delete stickers_[i].image;
                stickers_[i].image = nullptr;
            }
        }
        cap_ = max;
    }
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    Image* to_add = new Image(sticker);
    for (unsigned i = 0; i < cap_; i++) {
        if (stickers_[i].image == nullptr) {
            stickers_[i].image = to_add;
            stickers_[i].xcoord = x;
            stickers_[i].ycoord = y;
        }
        return i;
    }
    return -1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index >= cap_) {
        return false;
    }
    if (stickers_[index].image == nullptr) {
        return false;
    }
    stickers_[index].xcoord = x;
    stickers_[index].ycoord = y;
    return true;
}
void StickerSheet::removeSticker (unsigned index) {
    if (index < 0 || index >= cap_) {
        return;
    }
    delete stickers_[index].image;
    stickers_[index].image = nullptr;
}
Image* StickerSheet::getSticker (unsigned index) {
    if (index < 0 || index >= cap_) {
        return nullptr;
    }
    return stickers_[index].image;
}

Image StickerSheet::render() const {
    //find the bound
    unsigned max_x = base_ -> width();
    unsigned max_y = base_ -> height();
    for (unsigned i = 0 ; i < cap_; i++) {
        Sticker s = stickers_[i];
        if (s.image !=  nullptr) {
            max_x = max(max_x,s.xcoord + s.image -> width());
            max_y = max(max_y,s.ycoord + s.image -> height());
        }
    }
    
    Image* to_render = base_;
    to_render -> resize(max_x,max_y);
    to_render -> scale(max_x,max_y);


    for (unsigned int i = 0 ; i < cap_ ; i++) {
        Sticker curr = stickers_[i];
        if (curr.image == nullptr) {
            continue;
        }
        for (unsigned int h = 0 ; h < curr.image -> height(); h++) {
            for (unsigned int w = 0 ; w < curr.image -> width(); w++) {
                if (curr.image -> getPixel(w,h).a != 0) {
                    HSLAPixel& base_p = to_render-> getPixel(curr.xcoord+w,curr.ycoord+h);
                    HSLAPixel& rend_p = curr.image ->getPixel(w,h);
                    base_p = rend_p;
                }
            }
        }
    }
    return *to_render;
}

