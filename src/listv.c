#include "listv.h"
#include "listv_bar.h"
#include "menu.h"

GtkWidget *lv_win, *lv_box, *lv_tview, *lv_scrollw;
GtkListStore *lv_lstore;

void free_listv() {
  if (lv_win) {
    gtk_widget_hide(lv_win);
    lv_win = NULL;
  }
  if (lv_lstore){
    g_object_unref(lv_lstore);
    lv_lstore = NULL;
  }
  if (lv_tview){
    gtk_widget_destroy(lv_tview);
    lv_tview = NULL;
  }
  if (lv_scrollw){
    gtk_widget_destroy(lv_scrollw);
    lv_scrollw = NULL;
  }
  if (lv_box){
    gtk_widget_destroy(lv_box);
    lv_box = NULL;
  }
  if (lv_win){
    gtk_widget_destroy(lv_win);
    lv_win = NULL;
  }
}

void lv_importmodel(unsigned short numCols, char *titulos[]) {
  ushort i;
  if (lv_tview)
    gtk_widget_destroy(lv_tview);

  lv_tview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(lv_lstore));

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
    gtk_tree_view_append_column(GTK_TREE_VIEW(lv_tview), column);
  }

  gtk_container_add(GTK_CONTAINER(lv_scrollw), lv_tview);
  gtk_box_pack_start(GTK_BOX(lv_box), lv_scrollw, TRUE, TRUE, 0);
  gtk_widget_show_all(lv_win);
}

void init_listv(char *titulo) {
  free_listv();

  // Crear y configurar ventana principal
  lv_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(lv_win), 1280, 720);
  gtk_window_set_title(GTK_WINDOW(lv_win), titulo);
  gtk_window_set_position(GTK_WINDOW(lv_win), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(lv_win), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  // Crear contenedor principal de widgets
  lv_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  // Crear barra de búsqueda
  gen_bar();
  gtk_box_pack_start(GTK_BOX(lv_box), bar_box, FALSE, TRUE, 0);

  // Crear la ventana scrolleable
  lv_scrollw = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(lv_scrollw),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(lv_win), lv_box);
}
