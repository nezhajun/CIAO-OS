
#ifndef _STRING_H
#define _STRING_H

#include "types.h"

void memcpy(void* dst_, const void* src_, uint32_t size);
void memset(void* dst_, uint8_t value, uint32_t size);
char* strcpy(char* dst_, const char* src_);
uint32_t strlen(const char * str);
#endif // !_STRING_H