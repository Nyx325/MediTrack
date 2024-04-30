#include "datos/repositorio/linked_list.h"
#include "vista/app.h"
#include <stdlib.h>

void coso(LinkedList* list){
    int *a, *b, *c, *d;
    a = (int*)malloc(sizeof(int));
    b = (int*)malloc(sizeof(int));
    c = (int*)malloc(sizeof(int));
    d = (int*)malloc(sizeof(int));
    *a = 4;
    *b = 3;
    *c = 2;
    *d = 1;
    linkedlist_push(list, a);
    linkedlist_push(list, b);
    linkedlist_push(list, c);
    linkedlist_push(list, d);
    linkedlist_print(list);
}

int main(int argc, char **argv){
    gtk_init(&argc, &argv);

    App* app = app_new();

    LinkedList* list = linkedlist_new();
    coso(list);

    gtk_widget_show(app->win);
    //gtk_main();
    return 0;
}
