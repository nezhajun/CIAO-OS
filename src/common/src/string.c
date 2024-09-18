#include "string.h"

/* 将src_起始的size个字节复制到dst_ */
void memcpy(void* dst_, const void* src_, uint32_t size) {
//    ASSERT(dst_ != NULL && src_ != NULL);
   uint8_t* dst = dst_;
   const uint8_t* src = src_;
   while (size-- > 0)
      *dst++ = *src++;
}

/* 将dst_起始的size个字节置为value */
void memset(void* dst_, uint8_t value, uint32_t size) {
   // ASSERT(dst_ != NULL);
   uint8_t* dst = (uint8_t*)dst_;
   while (size-- > 0)
      *dst++ = value;
}

/* 将字符串从src_复制到dst_ */
char* strcpy(char* dst_, const char* src_) {
   // ASSERT(dst_ != NULL && src_ != NULL);
   char* r = dst_;		       // 用来返回目的字符串起始地址
   while((*r++ = *src_++));
   return r;
}

uint32_t strlen(const char * str)
{
   const char * p = str;
   while (*p++);
   return (p - str -1);
   
}