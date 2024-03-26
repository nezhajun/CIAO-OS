#ifndef __HTASK_H
#define __HTASK_H

#include "htask_core.h"

//hTaskErrorType hTask_init(hTask * hTask_t, void (*func_entry)(void *), void * param, hTaskStack * stack_t);
void hTaskIdle_thread();


#endif // !__HTASK_H