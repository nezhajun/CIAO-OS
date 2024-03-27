#ifndef _HLIST_H
#define _HLIST_H

typedef struct _hNode
{
    struct _hNode *prev;
    struct _hNode *next;
}hNode;

typedef struct _hList
{
    hNode * hNode_head;
    unsigned int Node_count;
}hList;

#define hNodeParent(node_t, parent, name) (parent*)((unsigned int)node_t - (unsigned int)&((parent *)0)->name)

void hNode_init(hNode * node_t);
void hList_init(hList * list_t);
uint32_t hList_count(hList * list_t);
void hListAddFirst (hList * list_t, hNode * node_t);
void hListRemove (hList * list_t, hNode * node_t);
hNode * hListPrev (hList * list_t, hNode * node_t);
hNode * hListNext (hList * list_t, hNode * node_t);
void hListRunCircle(hList * list_t);

#endif // !_HLIST_H
