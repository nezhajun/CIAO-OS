#include "htask_core.h"
#include "ARMCM3.h"

#define	NVIC_INT_CTRL			0xE000Ed04
#define	NVIC_PENDSVSET			0x10000000
#define	NVIC_SYSPRI2			0xE000ED22
#define	NVIC_PENDSV_PRI			0x000000FF

#define	MEM32(addr)				*(volatile unsigned long *)(addr)
#define	MEM8(addr)				*(volatile unsigned char *)(addr)

extern hTask * current_hTask;
extern hTask * next_hTask;

void hTaskRunFirst (void)
{
	__set_PSP(0);
	
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

void hTaskSwitch (void)
{
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

__asm void PendSV_Handler(void)
{
    import current_hTask
    import next_hTask

    mrs r0, psp
	cbz r0, hTaskRunfirst_

	stmdb r0!,{r4-r11}
	ldr r1,=current_hTask
	ldr r1, [r1]
	str r0, [r1]

hTaskRunfirst_
	ldr r0,=current_hTask
	ldr r1,=next_hTask
	ldr r2, [r1]
	str r2, [r0]

	ldr r0, [r2]
	ldmia r0! , {r4-r11}

	msr psp, r0
	orr lr,lr,#0x04
	bx lr
}
