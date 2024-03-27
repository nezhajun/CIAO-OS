#ifndef _HLOCK_H
#define _HLOCK_H

#include "htask_core.h"
#include "hlist.h"

typedef struct _SemaphoreType
{
    unsigned char value;
    hList hTaskWaitList;
}SemaphoreType;

typedef struct _hLock
{
    hTask * holder;
    SemaphoreType semaphore;
    unsigned int holder_repeat;
}hLock;



#endif // !_HLOCK_H
