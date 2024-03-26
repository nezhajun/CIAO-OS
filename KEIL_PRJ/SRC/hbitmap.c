#include "hbitmap.h"

void hBitmap_init(hBitmap * hBitmap_t)
{
    hBitmap_t->bitmap = 0;
}

void hBitmapSet (hBitmap * hBitmap_t, uint32_t pos)
{
    hBitmap_t->bitmap |=(1<<pos);
}

void hBitmapClear (hBitmap * hBitmap_t, uint32_t pos)
{
    hBitmap_t->bitmap &=(1<<pos);
}

uint32_t hBitmapGetFirstSet(hBitmap * hBitmap_t)
{
	static const uint8_t quickFindTable[] =
	{
		/* 00 */ 0xff, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 10 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 20 */ 5,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 30 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 40 */ 6,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 50 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 60 */ 5,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 70 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 80 */ 7,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* 90 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* A0 */ 5,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* B0 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* C0 */ 6,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* D0 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* E0 */ 5,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	    /* F0 */ 4,    0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0	
	};
	if (hBitmap_t->bitmap & 0xFF)
	{
		return quickFindTable[hBitmap_t->bitmap & 0xFF];
	}
	else if (hBitmap_t->bitmap & 0xFF00)
	{
		return quickFindTable[(hBitmap_t->bitmap >> 8) & 0xFF]+8;	
	}
	else if (hBitmap_t->bitmap & 0xFF0000)
	{
		return quickFindTable[(hBitmap_t->bitmap >> 16) & 0xFF]+16;		
	}
	else if (hBitmap_t->bitmap & 0xFF000000)
	{
		return quickFindTable[(hBitmap_t->bitmap >> 24) & 0xFF]+24;
	}
	else
	{
		return 32;
	}    
}


