#include "cbitmap.h"

void cBitmap_init(cBitmap * cBitmap_t)
{
    cBitmap_t->bitmap = 0;
}

void cBitmap_set (cBitmap * cBitmap_t, unsigned int pos)
{
    cBitmap_t->bitmap |=(1<<pos);
}

void cBitmap_clear (cBitmap * cBitmap_t, unsigned int pos)
{
    cBitmap_t->bitmap &=~(1<<pos);
}

unsigned int cBitmap_getFirstSet(cBitmap * cBitmap_t)
{
	static const unsigned char quickFindTable[] =
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
	if (cBitmap_t->bitmap & 0xFF)
	{
		return quickFindTable[cBitmap_t->bitmap & 0xFF];
	}
	else if (cBitmap_t->bitmap & 0xFF00)
	{
		return quickFindTable[(cBitmap_t->bitmap >> 8) & 0xFF]+8;	
	}
	else if (cBitmap_t->bitmap & 0xFF0000)
	{
		return quickFindTable[(cBitmap_t->bitmap >> 16) & 0xFF]+16;		
	}
	else if (cBitmap_t->bitmap & 0xFF000000)
	{
		return quickFindTable[(cBitmap_t->bitmap >> 24) & 0xFF]+24;
	}
	else
	{
		return 32;
	}    
}


