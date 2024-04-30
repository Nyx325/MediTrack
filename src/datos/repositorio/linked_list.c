#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* linkedList_new(){
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

void linkedList_push(LinkedList* list, void* element){
    if(list == NULL) return;

    if(list->size == 0){

    }
}

void linkedList_pop(LinkedList* list);
void linkedList_delete(LinkedList* list, void* element);
void linkedList_delete_index(LinkedList* list, unsigned long index);
