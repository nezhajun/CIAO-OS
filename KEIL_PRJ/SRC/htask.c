#include "htask.h"
#include "hlist.h"

hList hTaskReadyTable[32];
hList hTaskStop_List;
hList hTaskBlock_List;

hTask * current_hTask;
hTask * next_hTask;

hTaskStack hTaskIdle_env[64];
hTask hTaskIdle;

void hTaskReady_List_init()
{
    for (uint16_t i = 0; i < 32; i++)
        hList_init(&hTaskReadyTable[i]);
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
    hTask_t->state = TASK_READY;
    hNode_init(&(hTask_t->linkNode));
    tListAddFirst(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));

}

void hTask_schedule()
{
    // if( current_hTask ==  )
    
    hTaskSwitch();
}

void hTask_delay(uint32_t cnt)
{

}

void hTask_init()
{
    hTaskReady_List_init();
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

