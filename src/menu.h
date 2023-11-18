#ifndef MENU_H
#define MENU_H

#include "general.h"
#include "form_med.h"
#include "form_pac.h"
#include "form_prov.h"

extern GtkWidget *m_win;

void    gen_menu            (void);
void    pacientes           (GtkWidget *widget, gpointer data);
void    medicamento         (GtkWidget *widget, gpointer data);
void    proveedores         (GtkWidget *widget, gpointer data);
void    free_menu           (void);

#endif
