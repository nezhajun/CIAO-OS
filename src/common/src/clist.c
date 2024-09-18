#include "clist.h"

void cNode_init(cNode * node_t)
{
    node_t->next = node_t->prev = node_t;
}

void cList_init(cList * list_t)
{
    list_t->node_head = (void *)0;
    list_t->node_count = 0;
}

void cListAddFirst (cList * list_t, cNode * node_t)
{
    if( list_t->node_head == (void *)0) //only node_head
    {
        node_t->next = node_t->prev = node_t;
        list_t->node_head = node_t;
    }
    else
    {
        node_t->prev = list_t->node_head->prev;
        node_t->next = list_t->node_head;
        list_t->node_head->prev->next = node_t;
        list_t->node_head->prev = node_t;
    }

    list_t->node_count ++;
}

// void * cListRemoveFirst (cList * list_t)
// {
//     if( list_t->node_head == (void *)0) //first node
//     {
//         return;
//     }
//     else
//     {
//         node_t->prev = list_t->node_head->prev;
//         node_t->next = list_t->node_head;
//         list_t->node_head->prev->next = node_t;
//         list_t->node_head->prev = node_t;
//         list_t->node_count--;
//     }
// }

void cListRemove (cList * list_t, cNode * node_t)
{
    if( list_t->node_head == (void *)0) //only node_head
        return;
    if(list_t->node_head == node_t && node_t->next == node_t) // only one node
    {
        list_t->node_head = (void*)0;
		node_t->next = node_t->prev = node_t;
        list_t->node_count --;
    }
    else
    {
        if (list_t->node_head == node_t) //node_head point node_t
        {
            list_t->node_head = list_t->node_head->next; // change the node_head
        }
        node_t->prev->next = node_t->next;
        node_t->next->prev = node_t->prev;
        node_t->next = node_t->prev = node_t;
        list_t->node_count --;
    }
}

cNode * cListPrev (cList * list_t, cNode * node_t)
{
    if( list_t->node_head == (void *)0) //only node_head
        return list_t->node_head;
    return node_t->prev;
}

cNode * cListNext (cList * list_t, cNode * node_t)
{
    if( list_t->node_head == (void *)0) //only node_head
        return list_t->node_head;
    return node_t->next;
}

void cListRunCircle(cList * list_t)
{
    if( list_t->node_head == (void *)0) //first node
        return;
    list_t->node_head = list_t->node_head->next;
}


uint32_t cListCount(cList * list_t)
{
    return list_t->node_count;
}
