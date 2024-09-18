#ifndef _CTASK_H
#define _CTASK_H

#include "types.h"
#include "clist.h"

#define TASK_NAME_SIZE 32
#define TIME_SLICE_CNT 1

typedef uint32_t cStack;
typedef void cTaskfunc (void*);

typedef enum
{
    CTASK_RUNNING,
    CTASK_READY,
    CTASK_DELAY_BLOCKED,
    CTASK_SEM_BLOCKED,
    CTASK_STOP,
}cTaskState;

typedef enum
{
    CHOKE_DELAY,
    CHOKE_EVENT,
}cTaskChokeType;

typedef struct _task
{
    cStack * stack; // stack_point
    uint32_t * stack_base;
    uint32_t stack_size;
    cNode linkNode;
    char task_name[TASK_NAME_SIZE];
    uint32_t delay_ticks;
    uint32_t time_slice;
    uint32_t last_ticks;
    uint16_t priority;
    cTaskState state;
}cTask;

typedef struct
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebx;
    uint32_t ebp;
    void (* eip) (cTaskfunc * func, void * func_arg);
    void (* addr_dumy);
    cTaskfunc * func;
    void * func_arg;
}cStack_init_type;

void cTaskCreate(cTask * task_t, \
                const char * task_name_, \
                void (* func_entry)(void *), \
                void * param_, \
                uint16_t priority, \
                uint32_t time_slice_, \
                uint32_t * stack_base_, \
                uint32_t stack_size_);

extern void cTaskSwitchContext (cTask** task_from_t, cTask *task_to);
void cTaskSchedule(void);
cTask * cTask_getMaxPrio();
void cTask_start(cTask * ctask_t);
void cTask_param_init();
void cTaskSystemTickHandler(void);
void cTaskDelay(uint32_t delay_ticks);
void cTaskChoke(cTask * cTask_t,cTaskChokeType choke_type);

#endif // !_TASK_H