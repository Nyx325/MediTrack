#ifndef FORM_PROV_H
#define FORM_PROV_H

#include "general.h"
#include "listv.h"

void prov_crear_form                (Opc modo);
void mostrar_proveedores            (char *archivoDir);
void agregar_proveedor_callback     (GtkWidget *btn, gpointer data);
void modificar_proveedor_callback   (GtkWidget *btn, gpointer data);
void eliminar_datos_proveedor       (GtkWidget *btn, gpointer data);

#endif
