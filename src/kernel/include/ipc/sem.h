#ifndef SEM_H
#define SEM_H

#include "types.h"
#include "clist.h"

typedef struct sem_
{
    cList semList;
    uint32_t count;
}cSem;

void cSemInit(cSem * sem_t);
void cSemWait(cSem * sem_t);
void cSemNotify(cSem * sem_t);


#endif // !SEM_H
