#ifndef LOADER16_H
#define LOADER16_H

#include "types.h"

typedef int (*func_t)(void *);
// 内存检测信息结构
typedef struct SMAP_entry {
    uint32_t BaseL; // base address uint64_t
    uint32_t BaseH;
    uint32_t LengthL; // length uint64_t
    uint32_t LengthH;
    uint32_t Type; // entry Type
    uint32_t ACPI; // extended
}__attribute__((packed)) SMAP_entry_t;

struct gdt_entry{
    uint16_t limit_l;
    uint16_t base_l;
    uint16_t basehl_attr;
    uint16_t base_limit;
} __attribute__((aligned(8))); 

struct gdt_n
{
    uint16_t gdt_limit;
    uint32_t gdt_base;
}__attribute__((packed));

void loader16_init();
int show_message();
int enter_protect_mode();
int detect_mem_is_ok();
//void puts(const char * msg);
#endif // !LOADER16_H