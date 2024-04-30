#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef struct Node{
    void*           data;
    struct Node*    next;
    struct Node*    prev;
}Node;

Node*   node_new        (void* data);
void*   node_destroy    (Node **node);

#endif // !NODE_H
