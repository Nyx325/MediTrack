#include <gtk/gtk.h>
#include <glib.h>

GtkTreePath *selected_row = NULL;

void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata) {
    g_print("Fila seleccionada: %s\n", gtk_tree_path_to_string(path));
    // Guarda la fila seleccionada
    selected_row = gtk_tree_path_copy(path);
}

void on_button_clicked(GtkButton *button, gpointer user_data) {
    if (selected_row != NULL) {
        g_print("Botón clicado después de seleccionar una fila\n");
        gtk_tree_path_free(selected_row);
        selected_row = NULL;
    } else {
        g_print("Error: Debes seleccionar una fila antes de hacer clic en el botón.\n");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkListStore *list_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

    // Agregar 10 datos aleatorios al GtkListStore
    for (int i = 0; i < 10; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(list_store, &iter);

        gchar *data1 = g_strdup_printf("Fila %d, Columna 1", i + 1);
        gchar *data2 = g_strdup_printf("Fila %d, Columna 2", i + 1);

        gtk_list_store_set(list_store, &iter, 0, data1, 1, data2, -1);

        g_free(data1);
        g_free(data2);
    }

    GtkWidget *tree_view = gtk_tree_view_new();

    // Configurar las columnas para que se muestren
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Columna 1", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(tree_view, column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Columna 2", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(tree_view, column);

    // Asignar el modelo de datos (GtkListStore) al GtkTreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(list_store));

    GtkWidget *button = gtk_button_new_with_label("Realizar otra acción");

    // Conectar la señal "row-activated" para manejar la selección de fila
    g_signal_connect(tree_view, "row-activated", G_CALLBACK(on_row_activated), NULL);

    // Conectar la señal "clicked" del botón
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), tree_view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), vbox);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
