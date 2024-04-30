#include "linked_list.h"
#include <stdio.h>

LinkedList* linkedlist_new(){
    LinkedList* new = (LinkedList*)malloc(sizeof(LinkedList));
    if(new==NULL){
        printf("No se pudo crear la lista");
        return NULL;
    }

    new->size = 0;
    new->head = NULL;
    new->tail = NULL;

    return new;
}

int linkedlist_push(LinkedList* list, void* element){
    Node* node;
    if(list == NULL) return 1;
    //if(*list == NULL) return 1;

    if((list)->size == 0){
        node = node_new(element);
        if(node == NULL) return 0;
        (list)->head=node;
        (list)->tail=node;
        (list)->size++;
        return 1;
    }

    node = node_new(element);
    if(node == NULL) return 0;
    node->prev = (list)->tail;
    (list)->tail->next = node;
    (list)->tail = node;
    (list)->size++;
    return 1;
}

void linkedlist_print(LinkedList *list){
    if(list->size==0){
        printf("No existen elementos");
        return;
    }

    printf("Size: %lu\n", list->size);
    Node* node = list->head;
    printf("Tail: %p, Head: %p\n", list->tail, list->head);
    printf("Prev: %p, Cur: %p, Next: %p\n", node->prev, node, node->next);
    for(unsigned long i = 0; i<list->size; i++){
        int* dato = (int*)node->data;
        printf("%lu) %d\n", i, *dato);
        node = node->next;
    }
}

void linkedlist_pop(LinkedList* list){
    if(list->size == 0) return;

}
void linkedlist_delete(LinkedList* list, void* element);
void linkedlist_delete_index(LinkedList* list, unsigned long index);
