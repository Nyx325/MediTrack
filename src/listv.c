#include "general.h"
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

ListView tabla;

void free_baselistv(BaseListv *ventana) {
  if (ventana == NULL)
    return;

  if (!ventana->win)
    gtk_widget_destroy(ventana->win);
  if (!ventana->box)
    gtk_widget_destroy(ventana->box);
  if (!ventana->icon)
    g_object_unref(ventana->icon);
  if (!ventana->scrollWin)
    gtk_widget_destroy(ventana->scrollWin);

  ventana->win = NULL;
  ventana->box = NULL;
  ventana->icon = NULL;
  ventana->scrollWin = NULL;
}

void free_listview(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(tabla.baseVentana.win);

  if (!tabla.tView)
    gtk_widget_destroy(tabla.tView);
  if (!tabla.listStore)
    gtk_list_store_clear(tabla.listStore);
  if (!tabla.filaActual)
    g_object_unref(tabla.filaActual);

  free_baselistv(&tabla.baseVentana);

  tabla.tView = NULL;
  tabla.listStore = NULL;
  tabla.filaActual = NULL;
}

void listview_importmodel(ushort numCols, char *titulos[]) {
  ushort i;
  if (tabla.tView)
    gtk_widget_destroy(tabla.tView);

  tabla.tView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tabla.listStore));

  // Crear, configurar columnas y agregar al treeview
  for (i = 0; i < numCols; i++) {
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    GtkCellRenderer *render = gtk_cell_renderer_text_new();
    gtk_tree_view_column_set_title(column, titulos[i]);
    gtk_tree_view_column_pack_start(column, render, TRUE);
    gtk_tree_view_column_add_attribute(column, render, "text", i);
    // Configurar el tamaño de las columnas
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    // Ajustar propiedades para expandir
    gtk_tree_view_column_set_expand(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tabla.tView), column);
  }

  gtk_container_add(GTK_CONTAINER(tabla.baseVentana.scrollWin), tabla.tView);
  gtk_box_pack_start(GTK_BOX(tabla.baseVentana.box),
                     tabla.baseVentana.scrollWin, TRUE, TRUE, 0);

  gtk_widget_show_all(tabla.baseVentana.win);
}

void crear_ventana_listv(BaseListv *baseListv, int xRes, int yRes,
                         CallbackFunc callback) {
  baseListv->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_default_size(GTK_WINDOW(baseListv->win), xRes, yRes);
  gtk_window_set_position(GTK_WINDOW(baseListv->win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(baseListv->win), 20);
  g_signal_connect(G_OBJECT(baseListv->win), "destroy", G_CALLBACK(callback),
                   NULL);

  baseListv->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  // gtk_box_pack_start(GTK_BOX(tabla.baseVentana.box), bar_box, FALSE, TRUE,
  // 0);

  baseListv->scrollWin = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(baseListv->scrollWin),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(baseListv->win), baseListv->box);

  baseListv->icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(baseListv->win), baseListv->icon);
}

void listv_gen_table() {
    crear_ventana_listv(&tabla.baseVentana, 1280, 720, free_listview);
}
