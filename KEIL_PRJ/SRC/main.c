#include "main.h"
#include "htask.h"
#include "htask_test.h"

int main()
{  
    hTask_Param_init();
    htask_test();
    tSetSysTickPeriod();
    hTaskRunFirst();
    return 0;
}

