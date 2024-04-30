#include <gtk/gtk.h>
#include "vista/app.h"

int main(int argc, char **argv){
    gtk_init(&argc, &argv);

    App* app = app_new();

    gtk_widget_show(app->win);
    gtk_main();
    return 0;
}
