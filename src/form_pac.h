#ifndef FORM_PAC_H
#define FORM_PAC_H

#include "general.h"
#include "listv.h"



//void fp_wingrid();
void        gen_formpac     (GtkWidget *wid, gpointer data);
void        fp_aceptar      (GtkWidget *wid, gpointer data);
gboolean    reset_warning   (GtkWidget *widget, GdkEventButton *event, gpointer data);
int         addPaciente     (char nomPac[], Pacientes paciente);
void        mostrarPaci     (char nomPac[]);

#endif
