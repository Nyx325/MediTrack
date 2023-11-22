#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Crear una ventana
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Crear un GtkTextView y su buffer asociado
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Obtener la cadena que quieres cargar (puedes obtenerla de la entrada del usuario, archivo, etc.)
    const gchar *texto_a_cargar = "Texto de ejemplo como si lo hubiera ingresado el usuario.\nadlasdjasdhkas\nadadhladh";

    // Cargar la cadena en el buffer del GtkTextView
    gtk_text_buffer_set_text(buffer, texto_a_cargar, -1);

    // Crear un GtkScrolledWindow y agregar el GtkTextView a él
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Agregar el GtkScrolledWindow a la ventana
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
