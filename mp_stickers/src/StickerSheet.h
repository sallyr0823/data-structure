/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
 #ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "Image.h"
#include "cs225/PNG.h"
#pragma once
using namespace cs225;
class StickerSheet {
    public:

        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet ();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image* getSticker (unsigned index);
        Image render() const;
    private:
        struct Sticker {
            Image* image;
            unsigned xcoord;
            unsigned ycoord;
        };
        Image* base_ ;
        unsigned cap_;
        Sticker* stickers_;

        

};
#endif
