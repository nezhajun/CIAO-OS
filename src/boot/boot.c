
//__asm__(".code16gcc");
//asm(".code16gcc");
asm(".code16");
#include "boot.h"
#include "types.h"
#define LOAD16_ADDR 0x8000

void boot_entry()
{
    asm volatile (
        "addw $0x10,%%sp\n\t"
        "pop %%ebp\n\t"
        "push %%bp\n\t"
        "movw %%sp,%%bp\n\t"
        "sub $0x10,%%sp\n\t"
        :);

    asm volatile ("nop");
    //uint32_t a = 4;
    uint16_t a =4;
    uint16_t b =23;
    a = b +a;
    uint32_t c = a + b;
    c = c+b;
    asm volatile ("addl $2, %esp ");
    //return;
    ((void (*) (void))LOAD16_ADDR)();
}