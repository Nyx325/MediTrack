#ifndef LISTV_H
#define LISTV_H

#include "general.h"
#include "listv_bar.h"

typedef struct {
  GtkWidget *win;
  GtkWidget *box;
  GdkPixbuf *icon;
  GtkWidget *scrollWin;
} BaseListv;

typedef struct {
  BaseListv baseVentana;
  GtkWidget *tView;
  GtkListStore *listStore;
  GtkTreeSelection *filaActual;
} ListView;

extern ListView tabla;

void listv_gen_table        (void);
void free_listview          (GtkWidget *widget, gpointer data);
void listview_importmodel   (ushort numCols, char *titulos[]);

#endif

