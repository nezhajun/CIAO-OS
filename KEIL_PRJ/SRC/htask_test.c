#include "htask_core.h"
#include "htask_test.h"

extern hTask * current_hTask;
extern hTask * next_hTask;

hTaskStack hTask01_env[64];
hTaskStack hTask02_env[64];

hTask hTask01 =   { 
                    &hTask01_env[64], \
                    "hTask01", \
                    hTask01_func, \
                    (void *)0x1234, \
                    3 };
hTask hTask02 =   { 
                    &hTask02_env[64], \
                    "hTask02", \
                    hTask02_func, \
                    (void *)0x6978, \
                    3 };


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

}
