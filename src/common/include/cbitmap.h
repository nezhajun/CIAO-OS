#ifndef _CBITMAP_H
#define _CBITMAP_H

typedef struct _cBitmap
{
    unsigned int bitmap;
}cBitmap;

void cBitmap_init(cBitmap * cBitmap_t);
void cBitmap_set (cBitmap * cBitmap_t, unsigned int pos);
void cBitmap_clear (cBitmap * cBitmap_t, unsigned int pos);
unsigned int cBitmap_getFirstSet(cBitmap * cBitmap_t);

#endif // !_CBITMAP_H
