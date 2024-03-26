#ifndef __HTASK_H
#define __HTASK_H

#include "htask_core.h"

#define TIME_SLICE_CNT 10

//hTaskErrorType hTask_init(hTask * hTask_t, void (*func_entry)(void *), void * param, hTaskStack * stack_t);
void hTaskIdle_thread();


#endif // !__HTASK_H