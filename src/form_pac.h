#ifndef FORM_PAC_H
#define FORM_PAC_H

#include "general.h"

typedef struct{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct{
  char  nombre[50];
  char  CURP[19];
  Fecha fechas;
  char  sexo;
  char  telf[11];
  char  tpSangre[4];
  Fecha fechasC;
  int   estado;
}Pacientes;

//void fp_wingrid();
void        gen_formpac     (void);
void        fp_aceptar     (GtkWidget *wid, gpointer data);
gboolean    reset_warning   (GtkWidget *widget, GdkEventButton *event, gpointer data);
int         addPaciente     (char nomPac[], Pacientes paciente);

#endif
