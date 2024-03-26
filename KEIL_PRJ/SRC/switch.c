#include "htask_core.h"

extern hTask * current_hTask;
extern hTask * next_hTask;

__asm void PendSV_Handler(void)
{
    import current_hTask_t
    import next_hTask_t

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
