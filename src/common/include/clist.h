#ifndef _CLIST_H
#define _CLIST_H
#include "types.h"

typedef struct _cNode
{
    struct _cNode *prev;
    struct _cNode *next;
}cNode;

typedef struct _cList
{
    cNode * node_head;
    uint32_t node_count;
}cList;

#define cNodeParent(node_t, parent, name) (parent*)((uint32_t)node_t - (uint32_t)&((parent *)0)->name)

void cNode_init(cNode * node_t);
void cList_init(cList * list_t);
uint32_t cListCount(cList * list_t);
void cListAddFirst (cList * list_t, cNode * node_t);
void cListRemove (cList * list_t, cNode * node_t);
cNode * cListPrev (cList * list_t, cNode * node_t);
cNode * cListNext (cList * list_t, cNode * node_t);
void cListRunCircle(cList * list_t);

#endif // !_cList_H
