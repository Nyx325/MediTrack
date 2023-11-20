#ifndef FORM_PAC_H
#define FORM_PAC_H

#include "general.h"
#include "listv.h"

typedef struct {
  gchar *curp;
  gchar *nombre;
  gchar *fechaN;
  gchar *sexo;
  gchar *telf;
  gchar *tpSangre;
  gchar *fechaC;
  long  pos;
} PacientesSinFormato;

void pac_crear_form(Opc modo);
void mostrar_pacientes(char *archivoDir);
void pac_agregar_callback(GtkWidget *btn, gpointer data);
void pac_mod_callback(GtkWidget *btn, gpointer data);
void eliminar_datos_paciente(GtkWidget *btn, gpointer data);

#endif
