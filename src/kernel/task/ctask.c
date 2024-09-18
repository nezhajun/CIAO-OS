#include "ctask.h"
#include "printk.h"
#include "string.h"
#include "clist.h"
#include "cbitmap.h"
#include "cpu_instr.h"

cBitmap cTaskBitmap;
cList cTaskReadyTable[32]; /* 支持32 个优先级 */
cList cTaskStoplist;
cList cTaskBlockedList;
cList cTaskDelayList;

cTask * current_cTask_t;
cTask * next_cTask_t;

cTask task_idle;
uint32_t stack_idle[64];

static void cTask_func_loader(cTaskfunc * func_t, void * func_arg)
{
    asm volatile ("sti");
    func_t(func_arg);
}

cTask * cTask_getMaxPrio()
{
    uint32_t max_prio_pos = cBitmap_getFirstSet(&cTaskBitmap);
    cNode* node_t = cTaskReadyTable[max_prio_pos].node_head;
    return cNodeParent(node_t, cTask, linkNode);
}


void cTaskCreate(cTask * ctask_t, \
                const char * task_name_, \
                cTaskfunc * func_entry, \
                void * func_arg_, \
                uint16_t priority, \
                uint32_t time_slice_, \
                uint32_t * stack_base_, \
                uint32_t stack_size_)
{
    ASSERT(ctask_t != NULL && task_name_ != NULL && stack_base_ != NULL);
    ASSERT(stack_size_ > 48);
    ASSERT(strlen(task_name_) < TASK_NAME_SIZE );
    memset(stack_base_, 0, stack_size_);
    const char * n = task_name_;
    for ( uint8_t i =0; n[i] !='\0'; i++)
    {
        ctask_t->task_name[i] = n[i];
    }
    ctask_t->priority = priority;
    ctask_t->delay_ticks = 10;
    ctask_t->time_slice = time_slice_;
    ctask_t->last_ticks = ctask_t->time_slice;

    ctask_t->stack_base = stack_base_;
    ctask_t->stack_size = stack_size_;

    *(ctask_t->stack_base) = 0x20000612; /* magic number 读取该值可以判断栈有没有溢出 */
    ctask_t->stack = (void *) ( (uint32_t)stack_base_ + (uint32_t)(stack_size_) );

    ctask_t->stack = (cStack *)((uint32_t)ctask_t->stack - sizeof(cStack_init_type));
    cStack_init_type * cstack_init_t = ( cStack_init_type *)ctask_t->stack;
    cstack_init_t->addr_dumy = NULL; // 没有用
    cstack_init_t->ebp = cstack_init_t->ebx = cstack_init_t->edi = cstack_init_t->esi = 0;
    cstack_init_t->eip = cTask_func_loader;
    cstack_init_t->func_arg = func_arg_;
    cstack_init_t->func = func_entry;

    cNode_init(&(ctask_t->linkNode));
    // cListAddFirst(&cTaskReadyTable,&(ctask_t->linkNode));
    ctask_t->state = CTASK_STOP;
}


void cTask_start(cTask * ctask_t)
{
    cListAddFirst(&cTaskReadyTable[ctask_t->priority],&(ctask_t->linkNode));
    cBitmap_set(&cTaskBitmap,ctask_t->priority);
    ctask_t->state = CTASK_READY;
}

void cTaskSystemTickHandler(void)
{
    // if( hTaskScheduleState != ScheduleEnable )
    // {
    //     return;
    // }
    // uint32_t crit_tmp = cTaskEnterCritical(); /* 在 x86 中断中，中断一直关闭，所以这里不需要了*/
    if(--current_cTask_t->last_ticks == 0) // time slice turn run
    {
        current_cTask_t->last_ticks = current_cTask_t->time_slice;
        current_cTask_t->state = CTASK_READY;
        cTaskSchedule();
    }

    if( cTaskDelayList.node_head != (void *)0 )
    {
        uint32_t task_cnt;
        cNode* node_t = cTaskDelayList.node_head;
        for(task_cnt=cTaskDelayList.node_count; task_cnt>0; task_cnt--)
        {
            cTask * cTask_t = cNodeParent(node_t, cTask, linkNode);
            if( --cTask_t->delay_ticks == 0)
            {
                cListRemove(&cTaskDelayList,&(cTask_t->linkNode));
                cListAddFirst(&cTaskReadyTable[cTask_t->priority],&(cTask_t->linkNode));
                cBitmap_set(&cTaskBitmap,cTask_t->priority);
                cTask_t->state = CTASK_READY;
            }
            node_t = node_t->next;
        }
    }

    // cTaskExitCritical(crit_tmp);
}

void cTaskSchedule(void)
{
    cTask* cTaskPrio_t; 
    cListRunCircle(&cTaskReadyTable[current_cTask_t->priority]);
    cTaskPrio_t = cTask_getMaxPrio();

    if( current_cTask_t != cTaskPrio_t)
    {  
        next_cTask_t = cTaskPrio_t;
        next_cTask_t->state = CTASK_RUNNING;
        cTaskSwitchContext(&current_cTask_t, next_cTask_t);
    }
}


void cTask_param_init()
{
    cBitmap_init(&cTaskBitmap);
    for (uint8_t i = 0; i < 32; i++) cList_init(&cTaskReadyTable[i]);
    cList_init(&cTaskBlockedList);
    cList_init(&cTaskDelayList);
    cList_init(&cTaskStoplist);
}

cTask ctask_main;
cStack cstack_main[512];
extern void init_main(void *);

void task_main_init()
{
    cTaskCreate(
        &ctask_main,
        "task_main",
        init_main,
        "this is init_main...\r\n",
        3,
        10,
        cstack_main,
        sizeof(cstack_main)
    );
    cBitmap_set(&cTaskBitmap,ctask_main.priority);
    cListAddFirst(&cTaskReadyTable[ctask_main.priority],&ctask_main.linkNode);
    ctask_main.state = CTASK_RUNNING;
    // /cTask_start(&ctask_main);
    current_cTask_t = &ctask_main;
    asm volatile (
        "movl %0,%%esp\n\t"
        "popl %%edi\n\t"
        "popl %%esi\n\t"
        "popl %%ebx\n\t"
        "popl %%ebp\n\t"
        "ret\n\t"
        :
        :"r" (ctask_main.stack) );
}

void cTaskDelay(uint32_t delay_ticks)
{
    uint8_t crit_tmp = cTaskEnterCritical();
    if(current_cTask_t->state != CTASK_RUNNING)
    {
        cTaskExitCritical(crit_tmp);
        return;
    }
    current_cTask_t->delay_ticks = delay_ticks;
    cTaskChoke(current_cTask_t,CHOKE_DELAY); //这里只会执行 hTaskChoke 里的逻辑，但是hTaskChoke里面的调度函数不会执行
    cTaskExitCritical(crit_tmp);
}


void cTaskChoke(cTask * cTask_t,cTaskChokeType choke_type)
{
    uint8_t crit_tmp = cTaskEnterCritical();
    if(cTask_t->state != CTASK_RUNNING)
    {
        cTaskExitCritical(crit_tmp);
        return;
    }
    cTask_t->state = CTASK_DELAY_BLOCKED;

    cListRemove(&cTaskReadyTable[cTask_t->priority],&(cTask_t->linkNode)); // 链表元素增删处理必须保证先从A表删再增加到B表
    if (choke_type == CHOKE_DELAY) //CHOKE_DELAY
    {
        cListAddFirst(&cTaskDelayList,&(cTask_t->linkNode)); 
    }
    else  //CHOKE_EVENT
    {
        cListAddFirst(&cTaskBlockedList,&(cTask_t->linkNode));
    }

    if ( cTaskReadyTable[(cTask_t->priority)].node_head == (void *)0 )
    {
        cBitmap_clear(&cTaskBitmap,cTask_t->priority);
    }
    cTaskSchedule();
    cTaskExitCritical(crit_tmp);
}
// void cTaskRunFirst (void)
// {
//     next_cTask_t = hTaskGetMaxPrio();
//     next_cTask_t->state = CTASK_RUNNING;
//     cTaskSwitch();
// }