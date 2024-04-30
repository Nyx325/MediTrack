#include "app.h"

App* app_new(){
    App* new = (App*)malloc(sizeof(App));
    if(new == NULL){
        g_print("No hay suficiente memoria para crear la ventana");
        return NULL;
    }

    //CONFIG DE LA VENTANA
    new->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Establecer tamaño inicial a la ventana
    gtk_window_set_default_size(GTK_WINDOW(new->win), 1000, 500);
    gtk_window_maximize(GTK_WINDOW(new->win));
    //Establecer titulo
    gtk_window_set_title(GTK_WINDOW(new->win), "MediTrack");
    //Hacer que esté sentrada a la pantalla al mostrarse por primera vez
    gtk_window_set_position(GTK_WINDOW(new->win), GTK_WIN_POS_CENTER);
    // Establecer el padding entre widgets dentro de la venata y la ventana
    gtk_container_set_border_width(GTK_CONTAINER(new->win), 20);
    //Establecer icono
    new->icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
    gtk_window_set_icon(GTK_WINDOW(new->win), new->icon);
    // Configurar finalziacion del programa al cerrar la ventana
    g_signal_connect(G_OBJECT(new->win), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //No inicializamos el grid porque eso dependerá de la opcion de la app
    //que se vaya a abrir
    new->grid = NULL;
    return new;
}

// No creo que se llegue a usar esta funcion
// nunca pero de esta forma tendriamos que liberar
// en su mayoria la memoria de algunas cosas
void app_destroy(App** app){
    if(app == NULL) return;
    if(*app == NULL) return;

    if((*app)->win != NULL){
        gtk_widget_hide((*app)->win);
        gtk_widget_destroy((*app)->win);
    }
    
    if((*app)->grid != NULL) 
        gtk_widget_destroy((*app)->grid);

    if((*app)->icon != NULL)
        g_object_unref((*app)->icon);
    
    free(*app);
    *app = NULL;
}
