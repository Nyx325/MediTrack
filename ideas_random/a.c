#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *combo_box = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Opción 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Opción 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Opción 3");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 1);

    gtk_container_add(GTK_CONTAINER(window), combo_box);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
