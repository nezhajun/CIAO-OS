#include "hlist.h"

void hNode_init(hNode * node_t)
{
    node_t->next = node_t->prev = node_t;
}

void hList_init(hList * list_t)
{
    list_t->hNode_head = (void *)0;
    list_t->Node_count = 0;
}

uint32_t hList_count(hList * list_t)
{
    return list_t->Node_count;
}

void hListAddFirst (hList * list_t, hNode * node_t)
{
    if( list_t->hNode_head == (void *)0) //only hNode_head
    {
        node_t->next = node_t->prev = node_t;
        list_t->hNode_head == node_t;
    }
    else
    {
        node_t->prev = list_t->hNode_head->prev;
        node_t->next = list_t->hNode_head;
        list_t->hNode_head->prev->next = node_t;
        list_t->hNode_head->prev = node_t;
    }

    list_t->Node_count ++;
}

// void * hListRemoveFirst (hList * list_t)
// {
//     if( list_t->hNode_head == (void *)0) //first node
//     {
//         return;
//     }
//     else
//     {
//         node_t->prev = list_t->hNode_head->prev;
//         node_t->next = list_t->hNode_head;
//         list_t->hNode_head->prev->next = node_t;
//         list_t->hNode_head->prev = node_t;
//         list_t->Node_count--;
//     }
// }

void hListRemove (hList * list_t, hNode * node_t)
{
    if( list_t->hNode_head == (void *)0) //only hNode_head
        return;
    if(node_t->next == node_t) // only one node
    {
        list_t->hNode_head = (void*)0;
        list_t->Node_count --;
    }
    else
    {
        if (list_t->hNode_head == node_t) //hNode_head point node_t
        {
            list_t->hNode_head = list_t->hNode_head->next; // change the hNode_head
        }
        node_t->prev->next = node_t->next;
        node_t->next->prev = node_t->prev;
        node_t->next = node_t->prev = node_t;
        list_t->Node_count --;
    }
}

hNode * hListPrev (hList * list_t, hNode * node_t)
{
    if( list_t->hNode_head == (void *)0) //only hNode_head
        return list_t->hNode_head;
    return node_t->prev;
}

hNode * hListNext (hList * list_t, hNode * node_t)
{
    if( list_t->hNode_head == (void *)0) //only hNode_head
        return list_t->hNode_head;
    return node_t->next;
}

void hListRunCircle(hList * list_t)
{
    if( list_t->hNode_head == (void *)0) //first node
        return;
    list_t->hNode_head = list_t->hNode_head->next;
}

