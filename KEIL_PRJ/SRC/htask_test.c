#include "htask_core.h"
#include "htask_test.h"
#include "htask.h"

extern hTask * current_hTask;
extern hTask * next_hTask;

hTaskStack hTask01_env[64];
hTaskStack hTask02_env[64];

hTask hTask01;
hTask hTask02;


unsigned char flag01;
unsigned char flag02;
unsigned int num1;
unsigned int num2;

void delay_t(unsigned int cnt)
{
    while(--cnt);
}


void hTask01_func(void * param)
{
    num1 = *(unsigned int *)(param);
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
    num2 = *(unsigned int *)(param);
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
