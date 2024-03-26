#include "htask_core.h"

extern hTask * current_hTask_t;
extern hTask * next_hTask_t;

__asm void PendSV_Handler(void)
{
    import current_hTask_t
    import next_hTask_t

    mrs r0, psp
	cbz r0, hTaskfirst_

	stmdb r0!,{r4-r11}
	ldr r1,=current_hTask_t
	ldr r1, [r1]
	str r0, [r1]

hTaskfirst_
	ldr r0,=current_hTask_t
	ldr r1,=next_hTask_t
	ldr r2, [r1]
	str r2, [r0]

	ldr r0, [r2]
	ldmia r0! , {r4-r11}

	msr psp, r0
	orr lr,lr,#0x04
	bx lr
}
