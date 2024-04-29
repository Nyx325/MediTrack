#ifndef DEFAULT_WINDOW_H
#define DEFAULT_WINDOW_H

#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct{
    GtkWidget *win;
}DefaultWindow;

DefaultWindow* meditrack_new_default_window();

#endif // !DEFAULT_WINDOW_H
