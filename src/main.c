#include <gtk/gtk.h>
#include "vista/default_window.h"

int main(int argc, char **argv){
    gtk_init(&argc, &argv);

    DefaultWindow* win = meditrack_new_default_window();
    GtkWidget* label = gtk_label_new("Hola");

    gtk_widget_show(win->win);
    gtk_main();
    return 0;
}
