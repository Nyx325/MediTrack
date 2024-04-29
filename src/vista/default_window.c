#include "default_window.h"

DefaultWindow* meditrack_new_default_window(){
    DefaultWindow* new = (DefaultWindow*)malloc(sizeof(DefaultWindow));
    if(new == NULL){
        g_print("No hay suficiente memoria para crear la ventana");
        return NULL;
    }

    new->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(new->win), 1280, 720);
    gtk_window_set_title(GTK_WINDOW(new->win), "MediTrack");

    return new;
}
