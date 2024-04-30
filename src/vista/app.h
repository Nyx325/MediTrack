#ifndef APP_H
#define APP_H

#include <gtk/gtk.h>

typedef struct{
    GtkWidget *win;
    GtkWidget *grid;
    GdkPixbuf *icon;
}App;

App* app_new();
void app_destroy(App** app);

#endif // !APP_H
