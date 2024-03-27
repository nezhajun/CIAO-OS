#ifndef _HBITMAP_H
#define _HBITMAP_H

typedef struct _hBitmap
{
    unsigned int bitmap;
}hBitmap;

void hBitmap_init(hBitmap * hBitmap_t);
void hBitmapSet (hBitmap * hBitmap_t, unsigned int pos);
void hBitmapClear (hBitmap * hBitmap_t, unsigned int pos);
unsigned int hBitmapGetFirstSet(hBitmap * hBitmap_t);

#endif // !_HBITMAP_H
