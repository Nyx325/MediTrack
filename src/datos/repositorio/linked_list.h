#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <stdio.h>

typedef struct{
    unsigned long   size;
    Node*           head;
    Node*           tail;
}LinkedList;

LinkedList*     linkedlist_new          (void);
int             linkedlist_push         (LinkedList* list, void* element);
void*           linkedlist_pop          (LinkedList** list);
void            linkedlist_delete       (LinkedList* list, void* element);
void            linkedlist_delete_index (LinkedList* list, unsigned long index);
void            linkedlist_print        (LinkedList *list);

#endif // !LINKED_LIST_H
