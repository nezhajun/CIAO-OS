#include "init.h"
#include "boot_info.h"
#include "string.h"
#include "cpu.h"
#include "cpu_instr.h"
#include "irq.h"
#include "printk.h"
#include "timer.h"
#include "ctask.h"
#include "kernel_test.h"
#include "sem.h"

extern uint8_t __bss_start[];
extern uint8_t __bss_end[];
extern cSem signal01;
int a=1234;
const char b ='a';
const char chri[] = "Hello, world";
int aaaaa_[10];

static struct gdt_entry gdt_table[512] __attribute__((aligned(8))) =
{
    [0]={0},
    [1]={0xffff, 0x0000, 0x9a00, 0x00cf},
    [2]={0xffff, 0x0000, 0x9200, 0x00cf},
};


void kernel_init(boot_info_t * boot_info)
{
	/* clear .bss */
	memset((void *)__bss_start,0,((uint32_t)__bss_end - (uint32_t)__bss_start));

    uint64_t ram_total_size=0;
    boot_info_t boot_info_s = * boot_info;
    for (int i = 0; i < boot_info_s.ram_region_count ; i++)
    {
        ram_total_size = ram_total_size + boot_info_s.ram_region_cfg[i].size;
        /* code */
    }
    irq_disable_global();
    reload_gdt();
    printk(YELLOW"reload gdt..."RESET"\r\n");
    irq_init();
    printk(BLUE"irq_init..."RESET"\r\n");
    out_init();
    printk(GREEN"out_init..."RESET"\r\n");
    ASSERT( 1 < 2 );
    kernel_test();
    task_test();
    cSemInit(&signal01);
    task_main_init();

    // a = a / 0;
}



void init_main(void * arg)
{
    time_init();
    for(;;)
    {
        a++;
        // uint32_t if_status = cTaskEnterCritical();
        // printk("%s",arg);
        // cTaskExitCritical(if_status);
        // cTaskDelay(1000);
    }
}


void reload_gdt()
{
    cli();
    struct gdt_n gdt_n_t;
    gdt_n_t.gdt_limit = sizeof(gdt_table) - 1;
    gdt_n_t.gdt_base = (uint32_t)&gdt_table[0];
    lgdt((uint32_t)gdt_n_t.gdt_base, gdt_n_t.gdt_limit);
    uint32_t cr0 = read_cr0();
    write_cr0(cr0 | (1 << 0));
    asm volatile (
        "jmp $8, $refresh_cs_segment_\n\t"
        "refresh_cs_segment_:\n\t"
        "movw $16, %%ax\n\t"
        "movw %%ax, %%ds\n\t"
        "movw %%ax, %%gs\n\t"
        "movw %%ax, %%ss\n\t"
        "movw %%ax, %%es\n\t"
        "movw %%ax, %%fs\n\t"
        "movl $0x10000, %%eax\n\t"
        "sub $8, %%eax\n\t"
        "movl %%eax, %%esp"
        ::
    );
}


