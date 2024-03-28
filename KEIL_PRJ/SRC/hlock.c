#include "hlock.h"
#include "hlist.h"
#include "htask_core.h"

extern hTask * current_hTask_t;
extern ScheduleStateType hTaskScheduleState;
hLock hLockCur;

void sema_init(SemaphoreType *semaphore_t, unsigned char value)
{
    semaphore_t->value = value;
    hList_init(&(hLock_t->semaphore.hTaskWaitList));
}

void sem_up(SemaphoreType *semaphore_t)
{
    ScheduleStateType local_tmp;
    Schedule_Enter_Critical(hTaskScheduleState,local_tmp);
    if (semaphore_t->hTaskWaitList.hNode_head != (void *)0)
    {
        hNode * node_t = semaphore_t->hTaskWaitList.hNode_head;
        hTask * htask_t = hNodeParent(node_t, hTask, linkNode);
        hListRemove(&(semaphore_t->hTaskWaitList),node_t);
        hTaskWakeUp(htask_t);
    }
    semaphore_t->value++;
    Schedule_Exit_Critical(hTaskScheduleState,local_tmp);
    hTaskSchedule();
}

void hLock_init(hLock * hLock_t)
{
    hLock_t->holder = (void *)0;
    hLock_t->holder_repeat = 0;
    sema_init(&(hLockCur.semaphore),1);
    ScheduleStateInit(&hTaskScheduleState);
}

void hLock_acquire(hLock * hLock_t)
{
    ScheduleStateType local_tmp;
    Schedule_Enter_Critical(hTaskScheduleState,local_tmp);


    Schedule_Exit_Critical(hTaskScheduleState,local_tmp);
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