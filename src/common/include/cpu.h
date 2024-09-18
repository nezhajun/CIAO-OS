#ifndef CPU_H
#define CPU_H
#include "types.h"


#define SEG_G				(1 << 15)		// 设置段界限的单位，1-4KB，0-字节
#define SEG_D				(1 << 14)		// 控制是否是32位、16位的代码或数据段
#define SEG_P_PRESENT	    (1 << 7)		// 段是否存在

#define SEG_DPL0			(0 << 5)		// 特权级0，最高特权级
#define SEG_DPL3			(3 << 5)		// 特权级3，最低权限

#define SEG_S_SYSTEM		(0 << 4)		// 是否是系统段，如调用门或者中断
#define SEG_S_NORMAL		(1 << 4)		// 普通的代码段或数据段

#define SEG_TYPE_CODE		(1 << 3)		// 指定其为代码段
#define SEG_TYPE_DATA		(0 << 3)		// 数据段

#define SEG_TYPE_RW			(1 << 1)		// 是否可写可读，不设置为只读

#define GATE_TYPE_IDT		(0xE << 8)		// 中断32位门描述符
#define GATE_P_PRESENT		(1 << 15)		// 是否存在
#define GATE_DPL0			(0 << 13)		// 特权级0，最高特权级
#define GATE_DPL3			(3 << 13)		// 特权级3，最低权限


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

struct idt_entry{
	uint16_t offset15_0;
	uint16_t selector;
	uint16_t attr;
	uint16_t offset31_16;
}__attribute__((aligned(8))); 

#define KERNEL_SELECTOR_CS		(1 * 8)		// 内核代码段描述符
#define KERNEL_SELECTOR_DS		(2 * 8)		// 内核数据段描述符
#define KERNEL_STACK_SIZE       (8*1024)    // 内核栈
#define IDT_TABLE_NR		256 // IDT表项数量



#endif // !CPU_H