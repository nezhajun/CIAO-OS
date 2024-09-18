#include "kernel_test.h"
#include "printk.h"
#include "ctask.h"
#include "cpu_instr.h"
#include "sem.h"

cSem signal01;
cTask task01;
cStack stack_task01[256];
cTask task02;
cStack stack_task02[256];
char a_s[20] = "this is task01";
void task_test()
{
    cTask_param_init();
    
    cTaskCreate(&task01,"task01",func_task01,a_s,0,20,stack_task01,sizeof(stack_task01));
    cTaskCreate(&task02,"task02",func_task02,"this is task02",0,10,stack_task02,sizeof(stack_task02));
    cTask_start(&task01);
    cTask_start(&task02);

}

void func_task01(void * str)
{
    uint32_t cnt =0;
    for(;;)
    {
        cnt++;
        cSemNotify(&signal01);
        uint32_t if_status = cTaskEnterCritical();
        printk(GREEN"%s"RESET"\r\n",str);
        printk(GREEN"cnt=%d"RESET"\r\n",cnt);
        cTaskExitCritical(if_status);
        cTaskDelay(100);
    }
}

void func_task02(void * str)
{
    uint32_t cnt=0; 
    for(;;)
    {
        cnt++;
        cSemWait(&signal01);
        uint32_t if_status = cTaskEnterCritical();
        printk(YELLOW"%s"RESET"\r\n",str);
        printk(YELLOW"cnt=%d"RESET"\r\n",cnt);
        cTaskExitCritical(if_status);

        // cTaskDelay(100);
    }
}

void kernel_test()
{
    printk_test();
}

void printk_test()
{
    int a1=0;
    int a2=-53;
    int a3=15;
    // float f1=3.14159;
    printk("i love mos...\r\n");
    printk("i love mos...\r\n");
    printk("%c\r\n",'c');
    printk("%-5c\r\n",'c');
    printk("%05c\r\n",'c');
    printk("%c\r\n",'c');
    printk("%-5c\r\n",'c');
    printk("%05c\r\n",'c');
    printk("i love mos...\r\n");
    printk("%s\r\n","ahhh");
    printk("%-8s\r\n","ahhh");
    printk("%08s\r\n","ahhh");
    printk("i love mos...\r\n");
    printk("ak %s is %c...\r\n","math",'A');
    printk("panic at %s:%d (%s): \r\n", __FILE__, __LINE__, __func__);
    printk("a1=%d\r\n",a1);
    printk("a2=%d\r\n",a2);
    printk("a3=%d\r\n",a3);
    printk("a1=%b\r\n",a1);
    printk("a2=%b\r\n",a2);
    printk("a3=%b\r\n",a3);
    printk("a1=%u\r\n",a1);
    printk("a2=%U\r\n",a2);
    printk("a3=%u\r\n",a3);
    printk("a1=%x\r\n",a1);
    printk("a2=%x\r\n",a2);
    printk("a3=%x\r\n",a3);
    printk("a1=%X\r\n",a1);
    printk("a2=%X\r\n",a2);
    printk("a3=%X\r\n",a3);
    printk("a1=%d=%-3x=%03X=%b is ok\r\na2=%d=%x=%X=%b is ok\r\na3=%d=%-3x=%03X=%b is ok\r\n",\
a1,a1,a1,a1,   \
a2,a2,a2,a2,    \
a3,a3,a3,a3);

    // log_trace("log_log...");
    // log_debug("log_log...");
    // log_info("log_log...");
    // log_warn("log_log...");
    // log_error("log_log...");
    // log_fatal("log_log...");

}
