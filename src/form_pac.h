#ifndef FORM_PAC_H
#define FORM_PAC_H

#include <gtk/gtk.h>
#include "general.h"

//void fp_wingrid();
void gen_formpac();
void aceptar_opc(GtkWidget *wid, gpointer data);
gboolean reset_warning(GtkWidget *widget, GdkEventButton *event, gpointer data);

#endif
