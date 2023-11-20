#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wlnode {
  void *data;
  char desc[31];
  int id;
  struct wlnode *next;
} WlNode;

#define NO_DESC '\0'
#define NO_ID (-1)

WlNode *new_list();
WlNode *last_node(WlNode **list);
bool add_wlnode(WlNode **list, void *data, char desc[30], char ID);
WlNode *find_node(char desc[30], char id, WlNode **list);
void del_node(WlNode **node);

int main() {
  WlNode *lista = new_list(), *recorrido, *tmp;
  int dato[3], *pdatos[3], i;

  for (i = 0; i < 3; i++) {
    dato[i] = i;
    add_wlnode(&lista, &dato[i], "dato", i);
  }

  i = 0;
  recorrido = lista;
  while (recorrido != NULL) {
    pdatos[i] = (int *)recorrido->data;
    printf("pdato %d: %d\nSiguiente: %p\n\n", i, *pdatos[i], recorrido->next);
    recorrido = recorrido->next;
    i++;
  }

  recorrido = lista;
  while(recorrido!=NULL){
    tmp = recorrido;
    recorrido = recorrido->next;
    del_node(&tmp);
  }
}

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

bool add_wlnode(WlNode **list, void *data, char desc[30], char ID) {
  WlNode *new, *ultimo;

  new = (WlNode *)malloc(sizeof(WlNode));
  if (new == NULL)
    return false;

  new->data = data;
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
