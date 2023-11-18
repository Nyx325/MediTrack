#include <gtk/gtk.h>

int main() {
    // Datos de ejemplo en memoria (reemplaza esto con tus propios datos)
    guint8 data[] = {
        0xFF, 0x00, 0x00, 0xFF,  // Píxel 1: Rojo
        0x00, 0xFF, 0x00, 0xFF,  // Píxel 2: Verde
        0x00, 0x00, 0xFF, 0xFF   // Píxel 3: Azul
    };

    // Inicializa GTK
    gtk_init(NULL, NULL);

    // Crear una ventana GTK
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GdkPixbuf en una Ventana");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // Crear un GdkPixbufLoader y escribir los datos
    GdkPixbufLoader *loader = gdk_pixbuf_loader_new();
    gdk_pixbuf_loader_write(loader, data, sizeof(data), NULL);
    gdk_pixbuf_loader_close(loader, NULL);

    // Obtener el GdkPixbuf resultante
    GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);

    if (pixbuf) {
        // Crear un widget de imagen para mostrar el GdkPixbuf
        GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

        // Agregar el widget de imagen a la ventana
        gtk_container_add(GTK_CONTAINER(window), image);

        // Liberar recursos del GdkPixbuf y el loader
        g_object_unref(loader);
        g_object_unref(pixbuf);

        // Conectar la señal para cerrar la ventana
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        // Mostrar todo y entrar en el bucle principal de GTK
        gtk_widget_show_all(window);
        gtk_main();
    } else {
        g_print("No se pudo cargar la imagen desde memoria.\n");
    }

    return 0;
}
