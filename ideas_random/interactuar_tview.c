#include <gtk/gtk.h>

typedef struct Ventana {
  GtkWidget *win;
  GtkWidget *grid;
  GtkWidget *tview;
  GtkWidget *btn;
  GtkWidget *scrolledW;
  GtkListStore *liststore;
  GtkTreeSelection *filaSel;
} Ventana;

Ventana app;

void datos_por_fila(GtkWidget *btn, gpointer data) {
  GtkTreeModel *modelo;
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected(app.filaSel, &modelo, &iter)) {
    gchar *columna1;
    unsigned long pos;

    gtk_tree_model_get(modelo, &iter, 0, &columna1, 1, &pos, -1);

    g_print("Datos de la fila seleccionada:\n");
    g_print("Columna 1: %s\n", columna1);
    g_print("Columna 2: %ld\n", pos);

    g_free(columna1);
  } else {
    g_print("No se seleccionó una fila\n");
  }
}

void on_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                      GtkTreeViewColumn *column, gpointer userdata) {
  gchar *str_data;
  unsigned long pos;

  GtkTreeIter iter;
  GtkTreeModel *model = gtk_tree_view_get_model(treeview);

  if (gtk_tree_model_get_iter(model, &iter, path)) {
    gtk_tree_model_get(model, &iter, 0, &str_data, 1, &pos, -1);
    g_print("%s %ld\n", str_data, pos);
  }
}

int main() {
  gtk_init(NULL, NULL);

  app.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(app.win), 400, 300);
  g_signal_connect(G_OBJECT(app.win), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  app.grid = gtk_grid_new();

  app.liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_ULONG);

  GtkTreeIter iter;

  gtk_list_store_append(app.liststore, &iter);
  gtk_list_store_set(app.liststore, &iter, 0, "asdasdasdasdasd ", 1, 12, -1);
  gtk_list_store_append(app.liststore, &iter);
  gtk_list_store_set(app.liststore, &iter, 0, "asdasdasdasdasd ", 1, 12, -1);
  gtk_list_store_append(app.liststore, &iter);
  gtk_list_store_set(app.liststore, &iter, 0, "asdasdasdasdasd ", 1, 12, -1);

  app.tview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(app.liststore));
  app.filaSel = gtk_tree_view_get_selection(GTK_TREE_VIEW(app.tview));

  char *titulos[] = {"A", "B"};

  for (int i = 0; i < 2; i++) {
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    GtkCellRenderer *render = gtk_cell_renderer_text_new();
    gtk_tree_view_column_set_title(column, titulos[i]);
    gtk_tree_view_column_pack_start(column, render, TRUE);
    gtk_tree_view_column_add_attribute(column, render, "text", i);
    // Configurar el tamaño de las columnas
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    // Ajustar propiedades para expandir
    gtk_tree_view_column_set_expand(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(app.tview), column);
  }

  /*app.scrolledW = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(app.scrolledW),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(app.scrolledW), app.tview);*/
  gtk_grid_attach(GTK_GRID(app.grid), app.tview, 0, 0, 1, 1);
  // Conecta la señal "row-activated" a la función on_row_activated
  g_signal_connect(G_OBJECT(app.tview), "row-activated",
                   G_CALLBACK(on_row_activated), NULL);

  app.btn = gtk_button_new_with_label("Coso");
  g_signal_connect(app.btn, "clicked", G_CALLBACK(datos_por_fila), NULL);
  gtk_grid_attach(GTK_GRID(app.grid), app.btn, 0, 1, 1, 1);

  gtk_container_add(GTK_CONTAINER(app.win), app.grid);

  gtk_widget_show_all(app.win);

  gtk_main();
}
