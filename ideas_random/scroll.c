#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Crear un widget contenedor para el contenido del ScrolledWindow
    GtkWidget *container = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), container);

    // Crear contenido para el ScrolledWindow
    GtkWidget *label = gtk_label_new("Contenido del Scrolled Window");
    gtk_grid_attach(GTK_GRID(container), label, 1, 0, 1, 1);

    // Crear múltiples etiquetas a la izquierda
    for (int i = 1; i <= 30; i++) {
        GtkWidget *left_label = gtk_label_new(g_strdup_printf("Etiqueta Izquierda %d", i));
        gtk_grid_attach(GTK_GRID(container), left_label, 0, i, 1, 1);
    }

    // Crear múltiples etiquetas a la derecha
    for (int i = 1; i <= 30; i++) {
        GtkWidget *right_label = gtk_label_new(g_strdup_printf("Etiqueta Derecha %d", i));
        gtk_grid_attach(GTK_GRID(container), right_label, 2, i, 1, 1);
    }

    // Crear un widget de vista para que el contenido sea desplazable
    GtkWidget *view = gtk_viewport_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(view), scrolled_window);

    gtk_container_add(GTK_CONTAINER(window), view);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
