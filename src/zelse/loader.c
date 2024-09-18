#include "loader.h"
#include "i386_cpu.h"

struct gdt_entry_t gdt_entry[256] __attribute__((aligned(8))) =
{
    [0]=0,
    [1]={0xffff, 0x0000, 0x9a00, 0x00cf},
    [2]={0xffff, 0x0000, 0x9200, 0x00cf},
};

struct ards ards_t[5];


func_t init_sequence[] = 
{
    gdt_init,
    timer_init,
    page_init,
    NULL,
};


void _entry_()
{
    load_init();
    int mem_size = detect_memory();
    while (1)
    {
        /* code */
    }
    
}

void load_init()
{
    int a=1;
    int b=2;
    int c;
    c = a+b;
    func_t * func_t_p; 
    for (func_t_p = init_sequence; *func_t_p != NULL; func_t_p ++)
    {
        int res = (*func_t_p)(); 
        if (!res)
        {
        }
        
    }
    
}

int gdt_init(void)
{
    struct gdt_point_t gdt_point_s;
    get_gdt(&gdt_point_s);
    gdt_point_s.gdt_addr = (uint32_t)gdt_entry;
    gdt_point_s.gdt_length = sizeof(gdt_entry) - 1;
    load_gdt(&gdt_point_s);
    get_gdt(&gdt_point_s);
    return 0;
}

int timer_init(void)
{

}

int page_init(void)
{
    int a=1;
    return 0;
}

int detect_memory(void)
{
    int mem_size=-1;
    uint16_t ards_num=0;
    asm volatile(
        "xor %%ebx, %%ebx \n\t"
        "movl $0x534d4150, %%edx \n\t"
        "movl %1, %%edi \n\t"
        ".e820_mem_get_loop: \n\t"
        "movl $0xe820, %%eax \n\t"
        "movl $20, %%ecx \n\t"
        "int 0x15 \n\t"
        "jc .e820_failed_try_e810: \n\t"
        "add %%cx, %%di \n\t"
        "inc %0 \n\t"
        "cmp $0, %%ebx \n\t"
        "jnz .e820_mem_get_loop \n\t"
        ".e820_failed_try_e810: \n\t"
        "jmp . \n\t"
        :"+r"(ards_num),"+m"(ards_t)
        :
        :"eax", "ebx","ecx", "edx"
    );


//    asm volatile(
//        "mov $0x88, %%ah\n\t"
////        "int $0x0015\n\t" 
//       :"=a"(mem_size)
//    );
    return mem_size;
}

