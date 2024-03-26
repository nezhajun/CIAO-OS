#ifndef _HLIST_H
#define _HLIST_H

#include "stdint.h"

typedef struct _hNode
{
    struct _hNode *prev;
    struct _hNode *next;
}hNode;

typedef struct _hList
{
    hNode hNode_head;
    uint32_t Node_count;
}hList;

void hNode_init(hNode * hNode_t);
void hList_init(hList * hList_t);
uint32_t hList_count(void);
void tListAddFirst (hList * hList_t, hNode * node_t);

#endif // !_HLIST_H
