#include "htask_core.h"
#include "htask_test.h"
#include "htask.h"

extern hTask * current_hTask;
extern hTask * next_hTask;

hTaskStack hTask01_env[64];
hTaskStack hTask02_env[64];

hTask hTask01;
hTask hTask02;


uint8_t flag01;
uint8_t flag02;
uint32_t num1;
uint32_t num2;

void delay_t(uint32_t cnt)
{
    while(--cnt);
}


void hTask01_func(void * param)
{
    num1 = *(uint32_t *)(param);
    for (;;)
    {
        flag01 = 0;
        delay_t(100);
        flag01 = 1;
        delay_t(100);

    }
}


void hTask02_func(void * param)
{
    num2 = *(uint32_t *)(param);
    for (;;)
    {
        flag02 = 0;
        delay_t(100);
        flag02 = 1;
        delay_t(100);
    }
}

void htask_test()
{
    hTaskErrorType hTaskType;
    hTaskType = hTask_init(&hTask01, \
                            "hTask01", \
                            hTask01_func, \
                            (void *) 0, \
                            3 , \
                            &hTask01_env[64]);

    hTaskType = hTask_init(&hTask02,\
                            "hTask01",\
                            hTask02_func,\
                            (void *) 0, \
                            3 , \
                            &hTask02_env[64]);
}
