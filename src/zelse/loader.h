#ifndef _LOADER_H
#define _LOADER_H

#include "types.h"

typedef int (*func_t)(void);

struct gdt_entry_t{
    uint16_t limit_l;
    uint16_t base_l;
    uint16_t basehl_attr;
    uint16_t base_limit;
} __attribute__((aligned(8))); 

struct gdt_point_t 
{
    uint16_t gdt_length;
    uint32_t gdt_addr;
}__attribute__((packed));

struct ards
{
    uint32_t baseAddrLow;
    uint32_t baseAddrHigh;
    uint32_t lengthLow;
    uint32_t lengthHigh;
    uint32_t type; 
}__attribute__((packed));



void _entry_();
void load_init();
int gdt_init();
int page_init();
int timer_init();
int detect_memory();






#endif // !_LOADER_H
