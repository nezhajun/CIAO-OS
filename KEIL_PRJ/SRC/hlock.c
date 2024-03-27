#include "hlock.h"


void LockInit(hLock * hLock_t)
{
    hLock_t->holder = (void *)0;
    hLock_t->holder_repeat = 0;

}

