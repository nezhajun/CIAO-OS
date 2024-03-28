#ifndef __HTASK_CORE_H
#define __HTASK_CORE_H

#include "hlist.h"
#include "ARMCM3.h"

#define	NVIC_INT_CTRL			0xE000Ed04
#define	NVIC_PENDSVSET			0x10000000
#define	NVIC_SYSPRI2			0xE000ED22
#define	NVIC_PENDSV_PRI			0x000000FF

#define	MEM32(addr)				*(volatile unsigned long *)(addr)
#define	MEM8(addr)				*(volatile unsigned char *)(addr)

#define TASK_NAME_SIZE 20

typedef unsigned int hTaskStack;

typedef enum
{
    ScheduleEnable,
    ScheduleDisable,
}ScheduleStateType;


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
    TASK_SUSPEND,
    TASK_ZOMBIE,
}hTaskState;

typedef enum
{
    CHOKE_DELAY,
    CHOKE_EVENT,
}hTaskChokeType;

typedef struct _hTask
{
    hTaskStack * stack;
    hNode linkNode;
    char hTaskName[TASK_NAME_SIZE];
    unsigned int delay_ticks;
    unsigned int time_slice;
    unsigned int priority;
    hTaskState state;
}hTask;

#define Schedule_Enter_Critical(ScheduleState_,local_tmp_) { \
    local_tmp_ = ScheduleState_; \
    ScheduleState_ = ScheduleDisable; \
}

#define Schedule_Exit_Critical(ScheduleState_,local_tmp_) { \
    ScheduleState_ = local_tmp_; \
}

inline void hTaskSwitch (void)
{
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

#endif // !__HTASK_CORE_H
