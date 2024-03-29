#include "htask.h"
#include "hlist.h"
#include "hbitmap.h"

ScheduleStateType hTaskScheduleState;

hBitmap hTaskBitmap;

hList hTaskReadyTable[32];
hList hTaskBlockedList;
hList hTaskSuspendList;
hList hTaskDelayList;

hTask * current_hTask_t;
hTask * next_hTask_t;

hTaskStack hTaskIdle_env[64];
hTask hTaskIdle;
static hTask hTaskSnapshot;

unsigned int hTaskEnterCritical (void)
{
    unsigned int primask = __get_PRIMASK();
    __disable_irq();        // CPSID I
    return primask;
}

void hTaskExitCritical (unsigned int status) {
    __set_PRIMASK(status);
}

void ScheduleStateInit()
{ 
    hTaskScheduleState = ScheduleEnable;
}

hTask * hTaskGetMaxPrio()
{
    uint32_t max_prio_pos = hBitmapGetFirstSet(&hTaskBitmap);
    hNode* node_t = hTaskReadyTable[max_prio_pos].hNode_head;
    return hNodeParent(node_t, hTask, linkNode);
}

void hTaskList_init()
{
    uint16_t i;
    for (i = 0; i < 32; i++) hList_init(&hTaskReadyTable[i]);
    hList_init(&hTaskBlockedList); 
    hList_init(&hTaskSuspendList);
    hList_init(&hTaskDelayList);
}

void hTask_init(hTask * hTask_t,char * task_name,void (* func_entry)(void *),void * param,uint32_t priority, hTaskStack * stack)
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
    hTask_t->time_slice = TIME_SLICE_CNT;
    hTask_t->state = TASK_READY;

    for(unsigned int i=0;task_name[i]!='\0';i++)
    {
        hTask_t->hTaskName[i] = task_name[i];
    }
    
    hNode_init(&(hTask_t->linkNode));
    hListAddFirst(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));
    hBitmapSet(&hTaskBitmap,hTask_t->priority);
  
}

void tTaskSystemTickHandler(void)
{
    // if( hTaskScheduleState != ScheduleEnable )
    // {
    //     return;
    // }
    unsigned int crit_tmp = hTaskEnterCritical();    
    if(--current_hTask_t->time_slice == 0) // time slice turn run
    {
        current_hTask_t->time_slice = TIME_SLICE_CNT;
        hListRunCircle(&hTaskReadyTable[current_hTask_t->priority]);
        current_hTask_t->state = TASK_READY;
    }

    if( hTaskDelayList.hNode_head != (void *)0 )
    {
        unsigned int task_cnt;
        hNode* node_t = hTaskDelayList.hNode_head;
        for(task_cnt=hTaskDelayList.Node_count; task_cnt>0; task_cnt--)
        {
            hTask * hTask_t = hNodeParent(node_t, hTask, linkNode);
            if( --hTask_t->delay_ticks == 0)
            {
                hListRemove(&hTaskDelayList,&(hTask_t->linkNode));
                hListAddFirst(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));
                hBitmapSet(&hTaskBitmap,hTask_t->priority);
                hTask_t->state = TASK_READY;
            }
            node_t = node_t->next;
        }
    }

    hTaskSchedule();
    hTaskExitCritical(crit_tmp);
}

void hTaskSchedule(void)
{
    hTask* hTaskPrio_t;
    hTaskPrio_t = hTaskGetMaxPrio();

    if( current_hTask_t != hTaskPrio_t)
    {  
        next_hTask_t = hTaskPrio_t;
        next_hTask_t->state = TASK_RUNNING;
        hTaskSwitch();
    }
}


void hTaskChoke(hTask * hTask_t,hTaskChokeType choke_type)
{
    unsigned int crit_tmp = hTaskEnterCritical();
    if(hTask_t->state != TASK_RUNNING)
    {
        hTaskExitCritical(crit_tmp);
        return;
    }
    hTask_t->state = TASK_BLOCKED;

    hListRemove(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode)); // 链表元素增删处理必须保证先从A表删再增加到B表
    if (choke_type == CHOKE_DELAY) //CHOKE_DELAY
    {
        hListAddFirst(&hTaskDelayList,&(hTask_t->linkNode)); 
    }
    else  //CHOKE_EVENT
    {
        hListAddFirst(&hTaskBlockedList,&(hTask_t->linkNode));
    }

    if ( hTaskReadyTable[(hTask_t->priority)].hNode_head == (void *)0 )
    {
        hBitmapClear(&hTaskBitmap,hTask_t->priority);
    }
    hTaskSchedule();
    hTaskExitCritical(crit_tmp);
}


void hTaskWakeUp(hTask * hTask_t)
{
    unsigned int crit_tmp = hTaskEnterCritical();
    if( hTask_t->state != TASK_BLOCKED )
    {
				hTaskExitCritical(crit_tmp);
        return;        
    }
    hTask_t->state = TASK_READY;
    hListRemove(&hTaskBlockedList,&(hTask_t->linkNode));    
    hListAddFirst(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));
    hBitmapSet(&hTaskBitmap,hTask_t->priority);
    hTaskSchedule();
    hTaskExitCritical(crit_tmp);
}


void hTaskSuspend(hTask * hTask_t)
{
    unsigned int crit_tmp = hTaskEnterCritical();
    if(hTask_t->state != TASK_RUNNING && hTask_t->state != TASK_READY)
    {
        hTaskExitCritical(crit_tmp);
        return;
    }
    hTask_t->state = TASK_SUSPEND;
    hListRemove(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));
    hListAddFirst(&hTaskSuspendList,&(hTask_t->linkNode));
    if ( hTaskReadyTable[(hTask_t->priority)].hNode_head == (void *)0 )
    {
        hBitmapClear(&hTaskBitmap,hTask_t->priority);
    }
    hTaskSchedule();
    hTaskExitCritical(crit_tmp);
}


void hTaskResume(hTask * hTask_t)
{
    unsigned int crit_tmp = hTaskEnterCritical();
    if( hTask_t->state != TASK_SUSPEND )
    {
        hTaskExitCritical(crit_tmp);
        return;
    }
    hTask_t->state = TASK_READY;
    hListRemove(&hTaskSuspendList,&(hTask_t->linkNode));
    hListAddFirst(&hTaskReadyTable[hTask_t->priority],&(hTask_t->linkNode));
    hBitmapSet(&hTaskBitmap,hTask_t->priority);
    hTaskSchedule();
    hTaskExitCritical(crit_tmp);
}


void hTaskDelay(unsigned int ticks)
{
    unsigned int crit_tmp = hTaskEnterCritical();
    if(current_hTask_t->state != TASK_RUNNING)
    {
        hTaskExitCritical(crit_tmp);
        return;
    }
    current_hTask_t->delay_ticks = ticks;
    hTaskChoke(current_hTask_t,CHOKE_DELAY); //这里只会执行 hTaskChoke 里的逻辑，但是hTaskChoke里面的调度函数不会执行
    hTaskExitCritical(crit_tmp);
}

void hTask_Param_init(void)
{
    hBitmap_init(&hTaskBitmap);
    hTaskList_init();
    hTask_init(&hTaskIdle,\
                                        "Idle Task",\
                                        hTaskIdle_thread,\
                                        (void *) 0x44557, \
                                        31 , \
                                        &hTaskIdle_env[64]);


}

unsigned char idle_flag;
void hTaskIdle_thread(void * param)
{
    unsigned int * s = param;
    for (;;)
    {
        idle_flag = 0;
        delay_t(5000);
        idle_flag = 1;
        delay_t(5000);
    }
}


hTask hTaskGetInfo(void)
{
    hTaskSnapshot.delay_ticks = current_hTask_t->delay_ticks;
    hTaskSnapshot.linkNode = current_hTask_t->linkNode;
    hTaskSnapshot.priority = current_hTask_t->priority;
    hTaskSnapshot.stack = current_hTask_t->stack;
    hTaskSnapshot.state = current_hTask_t->state;
    hTaskSnapshot.time_slice = current_hTask_t->time_slice;
    for(unsigned int i=0; current_hTask_t->hTaskName[i]!='\0'; i++)
    {
        hTaskSnapshot.hTaskName[i] = current_hTask_t->hTaskName[i];
    }
    return hTaskSnapshot;
}


void hTaskRunFirst (void)
{
    next_hTask_t = hTaskGetMaxPrio();
    next_hTask_t->state = TASK_RUNNING;

	__set_PSP(0);
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}
