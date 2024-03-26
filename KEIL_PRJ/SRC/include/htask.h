#ifndef __HTASK_H
#define __HTASK_H

#include "htask_core.h"

#define TIME_SLICE_CNT 10


void hTaskList_init(void);
hTaskErrorType hTask_init(hTask * hTask_t,char * task_name,void (* func_entry)(void *),void * param,uint32_t priority, hTaskStack * stack);
void SysTick_Handler (void);
void hTaskSystemTick_Handler(void);
void hTaskSchedule(void);
void hTaskChoke(hTask * hTask_t);
void hTaskWakeUp(hTask * hTask_t);
void hTaskSuspend(hTask * hTask_t);
void hTaskResume(hTask * hTask_t);
void hTaskDelay(uint32_t ticks);
void hTask_Param_init(void);

void hTaskIdle_thread(void * param);

void hTaskRunFirst (void);

#endif // !__HTASK_H
