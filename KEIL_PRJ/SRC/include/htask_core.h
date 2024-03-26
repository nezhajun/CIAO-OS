#ifndef __HTASK_CORE_H
#define __HTASK_CORE_H

#include "stdint.h"
#include "hlist.h"

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
    uint32_t priority;
    hTaskState state;
}hTask;


#endif // !__HTASK_CORE_H