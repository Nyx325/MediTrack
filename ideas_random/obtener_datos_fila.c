#include <gtk/gtk.h>

enum { COL_ENTIDAD, COL_PROP, COL_ESTADO, NUM_COLS };

static void print_selected_row(GtkButton *button, gpointer user_data) {
    GtkTreeView *treeview = GTK_TREE_VIEW(user_data);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);

    // Obtener el modelo del árbol
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gchar *entidad;
        gchar *propiedad;
        gboolean estado;

        gtk_tree_model_get(model, &iter, COL_ENTIDAD, &entidad, COL_PROP, &propiedad, COL_ESTADO, &estado, -1);

        g_print("Entidad: %s\n", entidad);
        g_print("Propiedad: %s\n", propiedad);
        g_print("Estado: %s\n", estado ? "Verdadero" : "Falso");

        g_free(entidad);
        g_free(propiedad);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Crear el modelo de datos
    GtkListStore *liststore = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN);

    // Agregar datos de ejemplo al modelo
    GtkTreeIter iter;
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, COL_ENTIDAD, "Entidad1", COL_PROP, "Propiedad1", COL_ESTADO, TRUE, -1);
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, COL_ENTIDAD, "Entidad2", COL_PROP, "Propiedad2", COL_ESTADO, FALSE, -1);

    // Crear el TreeView
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore));

    // Definir títulos de las columnas
    const char *titulos[] = {"Entidad", "Propiedad", "Estado"};

    for (int i = 0; i < NUM_COLS; i++) {
        // Crear una columna para cada tipo de dato
        GtkTreeViewColumn *column = gtk_tree_view_column_new();
        gtk_tree_view_column_set_title(column, titulos[i]);

        // Agregar una celda de texto para las columnas de cadena
        GtkCellRenderer *renderer;
        if (i == COL_ENTIDAD || i == COL_PROP) {
            renderer = gtk_cell_renderer_text_new();
            gtk_tree_view_column_pack_start(column, renderer, TRUE);
            gtk_tree_view_column_add_attribute(column, renderer, "text", i);
        }

        // Agregar una celda de alternancia para la columna de estado
        else if (i == COL_ESTADO) {
            renderer = gtk_cell_renderer_toggle_new();
            gtk_tree_view_column_pack_start(column, renderer, TRUE);
            gtk_tree_view_column_add_attribute(column, renderer, "active", i);
        }

        // Agregar la columna al TreeView
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }

    // Configurar la selección como única (single selection)
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    // Botón para imprimir los datos de la fila seleccionada
    GtkWidget *button = gtk_button_new_with_label("Obtener Datos de la Fila Seleccionada");
    g_signal_connect(button, "clicked", G_CALLBACK(print_selected_row), treeview);

    // Mostrar la ventana
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), treeview, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
