#include <gtk/gtk.h>

void on_check_button_toggled(GtkWidget *widget, gpointer data) {
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
       g_print("Checkbox está seleccionado\n");
   } else {
       g_print("Checkbox no está seleccionado\n");
   }
}

int main(int argc, char *argv[]) {
   GtkWidget *window;
   GtkWidget *checkbutton;

   gtk_init(&argc, &argv);

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   checkbutton = gtk_check_button_new_with_label("Etiqueta del checkbox");

   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(checkbutton, "toggled", G_CALLBACK(on_check_button_toggled), NULL);

   gtk_container_add(GTK_CONTAINER(window), checkbutton);

   gtk_widget_show_all(window);

   gtk_main();

   return 0;
}

