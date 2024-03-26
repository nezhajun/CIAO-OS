#include "htask.h"
#include "hlist.h"
#include "hbitmap.h"

hBitmap hTaskBitmap;

hList hTaskReadyTable[32];
hList hTaskBlockedList;
hList hTaskStopList;

hTask * current_hTask_t;
hTask * next_hTask_t;

hTaskStack hTaskIdle_env[64];
hTask hTaskIdle;


hTask * hTaskGetMaxPrio()
{
    uint32_t max_prio_pos = hBitmapGetFirstSet(&hTaskBitmap);
    hNode* node_t = hTaskReadyTable[max_prio_pos].hNode_head;
    return hNodeParent(node_t, hTask, linkNode);
}

void hTaskList_init()
{
    for (uint16_t i = 0; i < 32; i++)
        hList_init(&hTaskReadyTable[i]);
    hList_init(&hTaskBlockedList); 
    hList_init(&hTaskStopList);
}

hTaskErrorType hTask_init(hTask * hTask_t,char * task_name,void (* func_entry)(void *),void * param,uint32_t priority, hTaskStack * stack)
{
    *(--stack) = (uint32_t)(1<<24); // xPSR
    *(--stack) = (uint32_t)func_entry; // PC
    *(--stack) = (uint32_t)0x14; // R14(LR)
    *(--stack) = (uint32_t)0x12; // R12
    *(--stack) = (uint32_t)0x03; // R3
    *(--stack) = (uint32_t)0x02; // R2
    *(--stack) = (uint32_t)0x01; // R1
    *(--stack) = (uint32_t)param; // R0

    // R11 - R4
    *(--stack) = (uint32_t)0x11; 
    *(--stack) = (uint32_t)0x10; 
    *(--stack) = (uint32_t)0x09; 
    *(--stack) = (uint32_t)0x08;
    *(--stack) = (uint32_t)0x07; 
    *(--stack) = (uint32_t)0x06; 
    *(--stack) = (uint32_t)0x05; 
    *(--stack) = (uint32_t)0x04;

    hTask_t->stack = stack;
    hTask_t->priority = priority;
    hTask_t->delay_ticks = 0;
    hTask_t->time_slice = _time_slice;
    hTask_t->time_slice = TIME_SLICE_CNT;
    hTask_t->state = TASK_READY;
    hNode_init(&(hTask_t->linkNode));
    tListAddFirst(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));
    hBitmapSet(&hTaskBitmap,hTask_t->priority);
}


void SysTick_Handler ()
{
	hTaskSystemTick_Handler();
}

void hTaskSystemTick_Handler()
{
    if(--current_hTask_t->time_slice == 0) // time slice turn run
    {
        current_hTask_t->time_slice == TIME_SLICE_CNT;
        hListRunCircle(&hTaskReadyTable[current_hTask_t->priority]);
        current_hTask_t->state = TASK_READY;
    }


    hTask_schedule();
}

void hTask_schedule()
{
    hTask* hTaskPrio_t = hTaskGetMaxPrio();
    if( current_hTask_t != hTaskPrio_t)
    {
        next_hTask_t = hTaskPrio_t;
        next_hTask_t->state = TASK_RUNNING;
        hTaskSwitch();
    }
}


void hTask_choke(hTask * hTask_t)
{
    if(hTask_t->state == TASK_READY || hTask_t->state == TASK_RUNNING)
    {
        hTask_t->state = TASK_BLOCKED;
        hListAddFirst(&hTaskBlockedList,hTask_t->linkNode);
        hListRemove(&hTaskReadyTable[hTask_t->priority],hTask_t->linkNode);
        hTask_schedule();
    }
}

void hTask_delay(uint32_t ticks)
{
    current_hTask_t->delay_ticks = ticks;
    hTask_choke(current_hTask_t);
}

void hTask_init()
{
    hBitmap_init(&hTaskBitmap);
    hTaskList_init();
    hTaskErrorType hTaskType = hTask_init(&hTaskIdle,\
                                        "Idle Task",\
                                        hTaskIdle_thread,\
                                        (void *) 0, \
                                        31 , \
                                        &hTaskIdle_env[64]);


}

void hTaskIdle_thread()
{

}

