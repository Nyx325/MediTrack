#include "widl.h"

WlNode *new_list() { return NULL; }

WlNode *last_node(WlNode **list) {
  WlNode *recorrido;
  if (*list == NULL)
    return NULL;

  recorrido = *list;
  while (recorrido->next != NULL)
    recorrido = recorrido->next;

  return recorrido;
}

bool add_wlnode(WlNode **list, GtkWidget *widget, GdkPixbuf *image,
                char desc[30], char ID) {
  WlNode *new, *ultimo;

  new = (WlNode *)malloc(sizeof(WlNode));
  if (new == NULL)
    return false;

  new->widget = widget;
  new->image = image;
  new->id = ID;
  strcpy(new->desc, desc);
  new->next = NULL;

  if (*list == NULL) {
    *list = new;
    return true;
  }

  ultimo = last_node(list);

  if (ultimo == NULL)
    return false;

  ultimo->next = new;

  return true;
}

WlNode *find_node(char desc[30], char id, WlNode **list) {
  WlNode *recorrido = *list;

  if (*list == NULL)
    return NULL;

  while (recorrido != NULL) {
    if (strcmp(recorrido->desc, desc) == 0 && recorrido->id == id)
      return recorrido;
  }

  return NULL;
}

void del_node(WlNode **node) {
  if (*node == NULL)
    return;

  (*node)->next = NULL;
  free(*node);
  *node = NULL;
}

void printwl(WlNode **list){
    WlNode *recorrido = *list;
    while(recorrido!=NULL){
        g_print("ID: %d, Dec: %s\n", recorrido->id, recorrido->desc);
        recorrido = recorrido->next;
    }
}
