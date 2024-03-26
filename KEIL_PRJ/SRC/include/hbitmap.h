#ifndef _HBITMAP_H
#define _HBITMAP_H

#include "stdint.h"

typedef struct _hBitmap
{
    uint32_t bitmap;
}hBitmap;

void hBitmap_init(hBitmap * hBitmap_t);
void hBitmapSet (hBitmap * hBitmap_t, uint32_t pos);
void hBitmapClear (hBitmap * hBitmap_t, uint32_t pos);
uint32_t hBitmapGetFirstSet(hBitmap * hBitmap_t);

#endif // !_HBITMAP_H
