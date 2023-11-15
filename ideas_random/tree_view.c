#include <gtk/gtk.h>

GtkWidget *scrollw, *tview, *win, *box;

void import_model(GtkListStore *model, unsigned short numCols,
                  char *titulos[]) {
  unsigned short i;
  tview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));

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
    gtk_tree_view_append_column(GTK_TREE_VIEW(tview), column);
  }

  // Crear la ventana scrolleable
  scrollw = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollw),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(scrollw), tview);
  gtk_box_pack_start(GTK_BOX(box), scrollw, TRUE, TRUE, 0);
}

int main() {
  gtk_init(NULL, NULL);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(win), 1280, 720);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  GtkListStore *list_store = gtk_list_store_new(
      8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
  GtkTreeIter iter; // estructura para identificar fila en modelo
  int i;
  for (i = 0; i < 20; i++) {
    gtk_list_store_append(list_store, &iter); // agregar fila nueva
    gtk_list_store_set(list_store, &iter, 0, "CURP-Valor", 1, "Nombre-Valor", 2,
                       "FechaN-Valor", 3, "Sexo-Valor", 4, "NumT-Valor", 5,
                       "TipoS-Valor", 6, "Fecha1C-Valor", 7, i, -1);
  }

  char *titulos[] = {"CURP", "Nombre",   "FechaN",   "Sexo",
                     "Telf", "TpSangre", "Primera C"};
  import_model(list_store, 7, titulos);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_widget_show_all(win);
  gtk_main();
}
