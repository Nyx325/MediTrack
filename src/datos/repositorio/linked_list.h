#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct Node{
    void* data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct{
    unsigned long size;
    Node* head;
    Node* tail;
}LinkedList;

LinkedList* linkedList_new();
void linkedList_push(LinkedList* list, void* element);
void linkedList_pop(LinkedList* list);
void linkedList_delete(LinkedList* list, void* element);
void linkedList_delete_index(LinkedList* list, unsigned long index);

#endif // !LINKED_LIST_H
