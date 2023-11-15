#ifndef GENERAL_H
#define GENERAL_H

#include <ctype.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char Opc;
typedef unsigned short ushort;

typedef struct {
  int   dia;
  int   mes;
  int   anio;
} Fecha;

typedef struct {
  char  nombre[50];
  char  CURP[19];
  Fecha fechas;
  char  sexo;
  char  telf[11];
  char  tpSangre[4];
  Fecha fechasC;
  int   estado;
} Pacientes;

void        cambio_mes          (GtkComboBox *widget, gpointer data);
char        dias_x_mes          (const gint mes);
char        *formatear_nombre   (const gchar *input);
gboolean    is_full_nums        (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    es_vocal_acentuada  (char c);
char        *formatear_num      (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    reset_warning       (GtkWidget *widget, GdkEventButton *event, gpointer data);
void        import_model        (GtkWidget *tview, GtkListStore *model, ushort numCols, char *titulos[]);

#endif
