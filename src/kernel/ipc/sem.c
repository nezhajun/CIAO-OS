#include "sem.h"
#include "cpu_instr.h"
#include "ctask.h"
#include "cbitmap.h" 
#include "clist.h"

extern cTask * current_cTask_t;
extern cTask * next_cTask_t;
extern cBitmap cTaskBitmap;
extern cList cTaskReadyTable[32]; /* 支持32 个优先级 */
extern cList cTaskStoplist;
extern cList cTaskBlockedList;
extern cList cTaskDelayList;
void cSemInit(cSem * sem_t)
{
    sem_t->count = 0;
    cList_init(& (sem_t->semList));
}

void cSemWait(cSem * sem_t)
{
    uint8_t crit_tmp = cTaskEnterCritical();
    if (sem_t->count > 0)
    {
        sem_t->count --;
    }else
    {
        cListRemove(&cTaskReadyTable[current_cTask_t->priority], &current_cTask_t->linkNode);
        current_cTask_t->state = CTASK_SEM_BLOCKED;
        if( cTaskReadyTable[current_cTask_t->priority].node_count == 0) cBitmap_clear(&cTaskBitmap,current_cTask_t->priority);
        cListAddFirst(&sem_t->semList, &current_cTask_t->linkNode);
        cTaskSchedule();
    }
    cTaskExitCritical(crit_tmp);
}

void cSemNotify(cSem * sem_t)
{
    uint8_t crit_tmp = cTaskEnterCritical();
    if( cListCount(&sem_t->semList))
    {
        cNode * node_t = sem_t->semList.node_head;
        cTask * cTask_t = cNodeParent(node_t, cTask, linkNode);
        cListRemove(&sem_t->semList,&cTask_t->linkNode);
        cTask_t->state = CTASK_READY;
        cListAddFirst(&cTaskReadyTable[cTask_t->priority],&cTask_t->linkNode);
        cBitmap_set(&cTaskBitmap,cTask_t->priority);
        cTaskSchedule();
    }else
    {
        sem_t->count ++;
    }
    cTaskExitCritical(crit_tmp);
}


