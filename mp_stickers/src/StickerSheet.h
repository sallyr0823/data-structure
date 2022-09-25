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
        void Clear();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image* getSticker (unsigned index);
        Image render() const;
    private:
        Image base_;
        Image** sheet_;
        unsigned* x_coord_;
        unsigned* y_coord_;
        unsigned int cap_;


        

};
#endif
