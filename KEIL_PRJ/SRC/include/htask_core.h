#ifndef __HTASK_CORE_H
#define __HTASK_CORE_H

#include "stdint.h"
#include "hlist.h"
#include "ARMCM3.h"

#define	NVIC_INT_CTRL			0xE000Ed04
#define	NVIC_PENDSVSET			0x10000000
#define	NVIC_SYSPRI2			0xE000ED22
#define	NVIC_PENDSV_PRI			0x000000FF

#define	MEM32(addr)				*(volatile unsigned long *)(addr)
#define	MEM8(addr)				*(volatile unsigned char *)(addr)

#define TASK_NAME_SIZE 20

typedef uint32_t hTaskStack;

typedef enum
{
    OKAY,
    OVERFLOW,
}hTaskErrorType;

typedef enum
{
    TASK_RUNNING,
    TASK_READY,
    TASK_BLOCKED,
    TASK_SUSPENDED,
    TASK_ZOMBIE,
}hTaskState;

typedef struct _hTask
{
    hTaskStack * stack;
    hNode linkNode;
    char hTaskName[TASK_NAME_SIZE];
    uint32_t delay_ticks;
    uint32_t time_slice;
    uint32_t priority;
    hTaskState state;
}hTask;


inline void hTaskRunFirst (void)
{
	__set_PSP(0);
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

inline void hTaskSwitch (void)
{
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

#endif // !__HTASK_CORE_H