#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Crear la ventana principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Panel de Búsqueda");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 60);

    // Crear un contenedor de caja horizontal para alinear los elementos
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // Crear botones
    GtkWidget *button1 = gtk_button_new_with_label("btn1");
    GtkWidget *button2 = gtk_button_new_with_label("btn2");
    GtkWidget *button3 = gtk_button_new_with_label("btn3");
    GtkWidget *button4 = gtk_button_new_with_label("btn4");

    // Crear entradas de texto
    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();

    // Agregar elementos al contenedor de la caja horizontal
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);

    // Agregar un separador (espacio) entre button3 y entry1
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox), separator, FALSE, FALSE, 20); // Cambia el valor 20 para ajustar la separación

    gtk_box_pack_start(GTK_BOX(hbox), button3, FALSE, FALSE, 0);

    // Agregar una barra separadora
    separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox), separator, FALSE, FALSE, 0);

    // Agregar las entradas de texto
    gtk_box_pack_start(GTK_BOX(hbox), entry1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry2, FALSE, FALSE, 0);

    // Agregar otra barra separadora
    separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox), separator, FALSE, FALSE, 0);

    // Agregar el cuarto botón
    gtk_box_pack_start(GTK_BOX(hbox), button4, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
