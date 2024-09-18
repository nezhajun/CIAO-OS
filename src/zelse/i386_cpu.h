#ifndef _I386_CPU_H
#define _I386_CPU_H

inline static void interrupt_off()
{
    asm volatile ("cli");
}

inline static void interrupt_on() 
{
    asm volatile ("sti");
}

inline static void load_gdt(struct gdt_point_t* gdt_ptr) {
    asm volatile ("lgdt (%0)" : : "r" (gdt_ptr));
}

inline static void get_gdt(struct gdt_point_t * gdt_ptr) {
    asm volatile ("sgdt %0" : "=m" (*gdt_ptr));
}

#endif // !_I386_CPU_H