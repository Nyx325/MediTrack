#ifndef REPORTES_H
#define REPORTES_H

#include "general.h"
#include "listv.h"


typedef struct {
  gchar *curp;
  gchar *nombre;
} rDatosPaciente;

typedef struct {
  char fecha[12];
  char presion[9];
  char temp[9];
  char imc[5];
  char altura[5];
  char peso[10];
  char dirArch[50];
} Buffer;

typedef struct {
  unsigned long numD;
  float prom;
} Promedio;

typedef struct {
  Promedio temp;
  Promedio imc;
  Promedio peso;
} Criterios;


void crear_reporte  (GtkWidget *btn, gpointer data);

#endif
