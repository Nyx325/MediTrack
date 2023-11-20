#include <gtk/gtk.h>

GtkWidget *child_window = NULL;  // Variable global para la ventana secundaria

void on_child_window_close(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(widget);  // Destruir la ventana y liberar los recursos
    child_window = NULL;  // Establecer la variable global en NULL
}

void show_new_window(GtkWidget *widget, gpointer data) {
    if (child_window == NULL) {
        child_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(child_window), 300, 200);

        GtkWidget *label = gtk_label_new("Contenido de la nueva ventana");
        gtk_container_add(GTK_CONTAINER(child_window), label);

        g_signal_connect(child_window, "destroy", G_CALLBACK(on_child_window_close), NULL);

        gtk_widget_show_all(child_window);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_button_new_with_label("Abrir nueva ventana");
    g_signal_connect(button, "clicked", G_CALLBACK(show_new_window), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
