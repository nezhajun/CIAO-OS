#include "hlist.h"

void hNode_init(hNode * hNode_t)
{
    hNode_t->next = hNode_t->prev = hNode_t;
}

void hList_init(hList * hList_t)
{
    hList_t->hNode_head.next = &(hList_t->hNode_head);
    hList_t->hNode_head.prev = hList_t->hNode_head.next;
    hList_t->Node_count = 0;

    

}

uint32_t hList_count(hList * hList_t)
{
    return hList_t->Node_count;
}

void tListAddFirst (hList * hList_t, hNode * node_t)
{
    node_t->next = hList_t->hNode_head.next;
    node_t->prev = &(hList_t->hNode_head);

    hList_t->hNode_head.next->prev = node_t;
    hList_t->hNode_head.next = node_t;
    hList_t->Node_count ++;
}

hNode * hListNext (hList * hList_t, hNode *node);
void tListRemoveAll (hList * hList_t);

void tListAddLast (hList * hList_t, hNode * node);
hNode * tListRemoveFirst (hList * hList_t);
void tListInsertAfter (hList * hList_t, hNode * nodeAfter, hNode * nodeToInsert);
void tListRemove (hList * hList_t, hNode * node);





