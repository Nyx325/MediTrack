#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear la ventana principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Centrar Grid y Redimensionar");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Crear un contenedor Grid
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear dos Entry
    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();

    // Agregar los widgets al Grid
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);

    // Crear una imagen
    GtkWidget *image = gtk_image_new_from_file("../images/MT2(2).png"); // Reemplaza "tu_imagen.png" con la ruta de tu imagen
    gtk_grid_attach(GTK_GRID(grid), image, 0, 2, 3, 1);

    // Configurar expansión y alineación en el Grid
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Conectar la señal "destroy" para cerrar la aplicación
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Iniciar el bucle principal de GTK
    gtk_main();

    return 0;
}
