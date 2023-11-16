#ifndef FORM_MED_H
#define FORM_MED_H

#include "form_pac.h"
#include "general.h"
#include <gtk/gtk.h>

void    gen_formed          (void);
void    fm_aceptar          (GtkWidget *wid, gpointer data);
int     agregarMedicamento  (char *archivoDir, Medicamento registro);

#endif  
