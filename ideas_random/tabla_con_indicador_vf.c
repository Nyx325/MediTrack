#include <gtk/gtk.h>

enum { COL_ENTIDAD, COL_PROP, COL_ESTADO, NUM_COLS };

static void on_cell_toggled(GtkCellRendererToggle *cell_renderer, gchar *path,
                            gpointer user_data) {
  GtkTreeModel *model = GTK_TREE_MODEL(user_data);
  GtkTreeIter iter;

  if (gtk_tree_model_get_iter_from_string(model, &iter, path)) {
    gboolean current_value;
    gtk_tree_model_get(model, &iter, COL_ESTADO, &current_value, -1);
    gtk_list_store_set(GTK_LIST_STORE(model), &iter, COL_ESTADO, !current_value,
                       -1);
  }
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // Crear el modelo de datos
  GtkListStore *liststore = gtk_list_store_new(NUM_COLS, G_TYPE_STRING,
                                               G_TYPE_STRING, G_TYPE_BOOLEAN);

  // Agregar datos de ejemplo al modelo
  GtkTreeIter iter;
  gtk_list_store_append(liststore, &iter);
  gtk_list_store_set(liststore, &iter, COL_ENTIDAD, "Entidad1", COL_PROP,
                     "Propiedad1", COL_ESTADO, TRUE, -1);
  gtk_list_store_append(liststore, &iter);
  gtk_list_store_set(liststore, &iter, COL_ENTIDAD, "Entidad2", COL_PROP,
                     "Propiedad2", COL_ESTADO, FALSE, -1);

  // Crear el TreeView
  GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore));

  // Crear una celda de tipo Toggle para la columna de estado
  GtkCellRenderer *renderer_toggle = gtk_cell_renderer_toggle_new();
  gtk_cell_renderer_toggle_set_activatable(
      GTK_CELL_RENDERER_TOGGLE(renderer_toggle), FALSE);

  // Agregar la columna de entidad
  GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
      "Entidad", gtk_cell_renderer_text_new(), "text", COL_ENTIDAD, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

  // Agregar la columna de propiedad
  column = gtk_tree_view_column_new_with_attributes(
      "Propiedad", gtk_cell_renderer_text_new(), "text", COL_PROP, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

  // Agregar la columna de estado con la celda Toggle
  column = gtk_tree_view_column_new_with_attributes("Estado", renderer_toggle,
                                                    "active", COL_ESTADO, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

  // Mostrar la ventana
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_add(GTK_CONTAINER(window), treeview);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
