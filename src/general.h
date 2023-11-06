#ifndef GENERAL_H
#define GENERAL_H

#include<gtk/gtk.h>
void cambio_mes(GtkComboBox *widget, gpointer data);
char dias_x_mes(const gint mes);

#endif