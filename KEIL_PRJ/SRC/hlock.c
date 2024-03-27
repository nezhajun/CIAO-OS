#include "hlock.h"
#include "hlist.h"
#include "htask_core.h"

extern hTask * current_hTask_t;
extern ScheduleStateType hTaskScheduleState;

void hLock_init(hLock * hLock_t)
{
    hLock_t->holder = (void *)0;
    hLock_t->holder_repeat = 0;
    hLock_t->semaphore.value = 1;
    hList_init(&(hLock_t->semaphore.hTaskWaitList));
    ScheduleStateInit(&hTaskScheduleState);
}

void hLock_acquire(hLock * hLock_t)
{
    ScheduleStateType local_tmp;
    Schedule_Enter_Critical(hTaskScheduleState,local_tmp);
    
}

void hLock_release(hLock * hLock_t)
{
    if( hLock_t->holder != current_hTask_t)
    {

    }
    else
    {
        hLock_t->holder_repeat++;
    }
}