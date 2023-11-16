#ifndef GENERAL_H
#define GENERAL_H

#include <ctype.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char Opc;
typedef unsigned short ushort;

typedef struct {
  int   dia;
  int   mes;
  int   anio;
} Fecha;

typedef struct medicamento {
  short         estado;
  unsigned int  id;
  char          marca[50];
  char          sustancia[50];
  float         gramaje;
  char          presentacion[50];
  char          laboratorio[50];
  unsigned int  unidadesCaja;
  float         costo;
  char          lote[20];
  Fecha         fecha;
  unsigned int  unidadesInventario;
}Medicamento;

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

typedef struct Proveedor {
  char  nombreComercial[100];
  char  nombreFactura[100];
  char  rfc[15];
  char  domicilio[100];
  char  numeroOficina[15];
  char  whatsappEmpresarial[15];
  char  correoElectronico[100];
  char  representanteComercial[100];
  ushort permisoNarcoticos;
  Fecha vigencia;
}Proveedor;

void        cambio_mes          (GtkComboBox *widget, gpointer data);
char        dias_x_mes          (const gint mes);
char        *formatear_nombre   (const gchar *input);
gboolean    is_full_nums        (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    is_number           (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    es_vocal_acentuada  (char c);
char        *formatear_num      (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    reset_warning       (GtkWidget *widget, GdkEventButton *event, gpointer data);
void        import_model        (GtkWidget *tview, GtkListStore *model, ushort numCols, char *titulos[]);
void        agregar_err         (char *texto, GString **cadena);
void        mostrarMed          (char nomMed[]);

#endif
