#ifndef WIDL_H
#define WIDL_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wlnode {
  GtkWidget *widget;
  GdkPixbuf *image;
  char desc[31];
  int id;
  struct wlnode *next;
} WlNode;

#define NO_DESC '\0'
#define NO_ID (-1)

WlNode *new_list();
WlNode *last_node(WlNode **list);
bool add_wlnode(WlNode **list, GtkWidget *widget, GdkPixbuf *image,
                char desc[30], char ID);
WlNode *find_node(char desc[30], char id, WlNode **list);
void del_node(WlNode **node);
void printwl(WlNode **list);

#endif
