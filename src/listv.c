#include "listv.h"
#include "listv_bar.h"

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

  free_barlistv(&tabla.bar);

  tabla.tView = NULL;
  tabla.listStore = NULL;
  tabla.filaActual = NULL;
}

void listview_importmodel(ListView *lviewStruct, ushort numCols, char *titulos[]) {
  ushort i;
  if (lviewStruct->tView)
    gtk_widget_destroy(lviewStruct->tView);

  lviewStruct->tView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(lviewStruct->listStore));
  lviewStruct->filaActual = gtk_tree_view_get_selection(GTK_TREE_VIEW(lviewStruct->tView));

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
    gtk_tree_view_append_column(GTK_TREE_VIEW(lviewStruct->tView), column);
  }

  gtk_container_add(GTK_CONTAINER(lviewStruct->baseVentana.scrollWin), lviewStruct->tView);
  gtk_box_pack_start(GTK_BOX(lviewStruct->baseVentana.box),
                     lviewStruct->baseVentana.scrollWin, TRUE, TRUE, 0);

  gtk_widget_show_all(lviewStruct->baseVentana.win);
}

guint crear_ventana_listv(BaseListv *baseListv, int xRes, int yRes) {
  guint handler_id;
  baseListv->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_default_size(GTK_WINDOW(baseListv->win), xRes, yRes);
  gtk_window_set_position(GTK_WINDOW(baseListv->win), GTK_WIN_POS_CENTER);
  handler_id = g_signal_connect(G_OBJECT(baseListv->win), "destroy",
                                G_CALLBACK(gtk_main_quit), NULL);

  baseListv->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  baseListv->scrollWin = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(baseListv->scrollWin),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(baseListv->win), baseListv->box);

  baseListv->icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(baseListv->win), baseListv->icon);

  return handler_id;
}

void listv_gen_table(Opc tipoBar) {
  crear_ventana_listv(&tabla.baseVentana, 1280, 720);

  tabla.bar = crear_bar(tipoBar);
  gtk_box_pack_start(GTK_BOX(tabla.baseVentana.box), tabla.bar.mainbox, FALSE,
                     FALSE, 0);

  gtk_widget_show_all(tabla.baseVentana.win);
}
