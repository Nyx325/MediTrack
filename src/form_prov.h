#ifndef FORM_PROV_H
#define FORM_PROV_H

#include "general.h"

void gen_formprov       (void);
void agregarProveedor   (char *dirArchivo, Proveedor proveedor);
void prov_aceptar       (GtkWidget *Wid, gpointer data);

#endif
