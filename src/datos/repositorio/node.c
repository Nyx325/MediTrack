#include "node.h"
#include <stdio.h>

Node* node_new(void* data){
    Node* new = (Node*)malloc(sizeof(Node));

    if(new==NULL){
        printf("No se pudo crear el nodo");
        return NULL;
    }

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    return new;
}

void* node_destroy(Node **node){
    if(node==NULL) return NULL;
    if(*node==NULL) return NULL;
    
    void* tmp = (*node)->data;

    free(*node);
    (*node) = NULL;

    return tmp;
}
