#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "general.h"
#include "listv.h"

void free_tabla_consultas           (GtkWidget *widget, gpointer data);
void crear_tabla_consultas          (GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void crear_formulario_consulta      (Opc modo);
void agregar_consulta_callback      (GtkWidget *btn, gpointer data);
void modificar_consulta_callback    (GtkWidget *btn, gpointer data);
void eliminar_datos_consulta        (GtkWidget *btn, gpointer data);

typedef struct {
  GtkWidget *lblTitulo;
  GtkWidget *textv;
  GtkTextBuffer *buffer;
  GtkWidget *numcEscritos;
  GtkWidget *scrollW;
  GtkWidget *frame;
  int maxChars;
} EntradaTextv;

typedef struct{
    GtkWidget *lbl;
    GtkWidget *sistEntry;
    GtkWidget *diastEntry;
}EntradaPresion;

typedef struct {
  BaseForm          baseForm;
  EntradaTexto      nomPac;
  EntradaFecha      fConsulta;
  EntradaTexto      edad;
  EntradaTexto      peso;
  EntradaTexto      altura;
  EntradaTexto      nomDr;
  EntradaTexto      temp;
  EntradaTextv      sintomas;
  EntradaTextv      alergias;
  EntradaTextv      enfCron;
  EntradaPresion    presion;
  GtkWidget         *warningLbl;
  GtkWidget         *aceptBtn;
  GtkWidget         *cancelBtn;
} ConsForm;

#endif
