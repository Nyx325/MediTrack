#ifndef FORM_MED_H
#define FORM_MED_H

#include "general.h"

void med_crear_form                     (Opc modo);
void mostrar_medicamentos               (char *archivoDir);
void agregar_medicamentos_callback      (GtkWidget *btn, gpointer data);
void modificar_medicamentos_callback    (GtkWidget *btn, gpointer data);
void eliminar_datos_medicamentos        (GtkWidget *btn, gpointer data);

#endif
