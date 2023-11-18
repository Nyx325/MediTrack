#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wl_node {
  void *data;
  char desc[31];
  char id;
  struct wl_node *prev;
  struct wl_node *next;
} WlNode;

#define NO_DESC '\0'
#define NO_ID (-1)

void add_wlnode(WlNode **list, void *data, char desc[30], char id);
WlNode *first_node(WlNode **list);
WlNode *last_node(WlNode **list);
void del_node(WlNode **node);
void printwl(WlNode **first_node);
WlNode *find_node(char desc[11], char id, WlNode **list);


void add_wlnode(WlNode **list, void *data, char desc[30], char id) {
  WlNode *new = (WlNode *)malloc(sizeof(WlNode));
  if (new == NULL) {
    g_print("No se pudo asignar memoria\n");
    return;
  }

  new->data = data;
  strcpy(new->desc, desc);
  new->id = id;

  if (*list == NULL) {
    new->next = NULL;
    new->prev = NULL;
  } else {
    new->prev = *list;
    new->next = NULL;
    (*list)->next = new;
  }

  *list = new;
}

WlNode *first_node(WlNode **list) {
  WlNode *recorrido;
  if (*list == NULL) {
    g_print("Lista vacía\n");
    return NULL;
  }

  recorrido = *list;
  while (recorrido->prev != NULL) {
    recorrido = recorrido->prev;
  }

  return recorrido;
}

WlNode *last_node(WlNode **list) {
  WlNode *recorrido;
  if (*list == NULL) {
    g_print("Lista vacia\n");
    return NULL;
  }

  recorrido = *list;
  while (recorrido->next != NULL) {
    recorrido = recorrido->next;
  }

  return recorrido;
}

void del_node(WlNode **node) {
  if (*node == NULL) {
    printf("nodo nulo\n");
    return;
  }

  if ((*node)->prev != NULL)
    (*node)->prev->next = (*node)->next;

  if ((*node)->next != NULL)
    (*node)->next->prev = (*node)->prev;

  (*node)->next = NULL;
  (*node)->prev = NULL;

  free(*node);
  *node =
      NULL; // Establece el puntero a NULL para evitar referencias incorrectas.
}

void printwl(WlNode **first_node) {
  WlNode *recorrido = *first_node;

  while (recorrido != NULL) {
    printf("Desc: %s ID: %d, next: %p\n", recorrido->desc, recorrido->id,
           recorrido->next);
    recorrido = recorrido->next;
  }
}

// El nodo list debe ser el primero o el úmtimo
// TODO usar hilos para buscar en ambas direcciones(?)
WlNode *find_node(char desc[30], char id, WlNode **list) {
  WlNode *recorrido = *list;

  if (*list == NULL || ((*list)->prev != NULL && (*list)->next != NULL))
    return NULL;

  if ((*list)->prev == NULL) {
    while (recorrido != NULL) {
      if (strcmp(recorrido->desc, desc) == 0 && recorrido->id == id)
        return recorrido;
      recorrido = recorrido->next;
    }
  } else if ((*list)->next == NULL) {
    while (recorrido != NULL) {
      if (strcmp(recorrido->desc, desc) == 0 && recorrido->id == id)
        return recorrido;
      recorrido = recorrido->prev;
    }
  }

  return NULL;
}
