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
  int       estado;
  char      nombreComercial[100];
  char      nombreFactura[100];
  char      rfc[15];
  char      domicilio[100];
  char      numeroOficina[11];
  char      whatsappEmpresarial[11];
  char      correoElectronico[100];
  char      representanteComercial[100];
  ushort    permisoNarcoticos;
  Fecha     vigencia;
}Proveedor;

typedef void (*CallbackFunc)(GtkWidget *, gpointer);

void        cambio_mes              (GtkComboBox *widget, gpointer data);
char        dias_x_mes              (const gint mes);
char        *formatear_nombre       (const gchar *input);
char        *formatear_palabra      (const gchar *input);
gboolean    is_full_nums            (const gchar *input, gsize max_tam, gsize min_tam);
char        *formatear_telf         (const gchar *input);
gboolean    is_number               (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    es_vocal_acentuada      (char c);
char        *formatear_num          (const gchar *input);
gboolean    reset_warning           (GtkWidget *widget, GdkEventButton *event, gpointer data);
void        import_model            (GtkWidget *tview, GtkListStore *model, ushort numCols, char *titulos[]);
void        agregar_err             (char *texto, GString **cadena);
void        mostrarMed              (char nomMed[]);
int         formatear_tsangre_num   (char *tipoS);
void        imprimir_paciente       (Pacientes p);
gboolean    gchar_a_char            (gchar *cadenaOrigen, char *cadenaDestino);
gboolean    fechaGchar_a_int        (gchar *entrada, Fecha *salida);
void        gchar_a_int             (gchar *entrada, int *dato);
gboolean    gchar_a_uint            (gchar *entrada, unsigned int *dato);
void        gchar_a_float           (gchar *entrada, float *dato);


typedef struct {
  GtkWidget *lbl;
  GtkWidget *entry;
} EntradaTexto;

typedef struct {
  GtkWidget *anioEntry;
  GtkWidget *mesCombox;
  GtkWidget *diaCombox;
  GtkWidget *titulo;
} EntradaFecha;

typedef struct {
  GtkWidget *combox;
  GtkWidget *lbl;
} EntradaCombox;

typedef struct{
  GtkWidget *win;
  GtkWidget *grid;
  GdkPixbuf *icon;
}BaseForm;

typedef void (*CallbackFunc)(GtkWidget *, gpointer);

void        free_entradatexto   (EntradaTexto *entrada);
void        free_entradafecha   (EntradaFecha *fecha);
void        free_entradacombox  (EntradaCombox *entrada);
void        free_baseform       (BaseForm *basesVentana);
void        crear_entradatexto  (EntradaTexto *info, char *titulo, int tamEntry, int maxChars);
void        crear_entradafecha  (EntradaFecha *fecha, char *titulo);
void        crear_entradacombox (EntradaCombox *entrada, char *titulo, const gchar *datos[], int length);
void        crear_boton         (GtkWidget **btn, char *titulo, CallbackFunc callback);
void        crear_ventana       (BaseForm *baseDelFormulario, int xRes, int yRes, CallbackFunc callback);


typedef struct {
  GtkWidget *img;
  GtkWidget *btn;
} BtnBase;

void free_basebtn(BtnBase *bBtn);

typedef struct {
  const gchar   *textoEntry;
  char          *entradaFormato;
} TextoIngresado;

typedef struct {
  const gchar *anio;
} FechaIngresada;

typedef struct {
  GtkEntry *anioEntry;
  GtkComboBox *mesCombox;
  GtkComboBox *diaCombox;
} WidgetsFecha;

// Puntero a una función que retorna una dir a un array char y recibe un array tipo gchar
typedef char* (*FuncFormato)(const gchar *);

void capturar_formatear_texto   (TextoIngresado *dato, char *registro, FuncFormato funcion, GtkWidget *entry, GString **err, char *errNom);
void capturar_formatear_fecha   (FechaIngresada *fecha, WidgetsFecha *widgets, Fecha *fechaReg, GString **err, char *errNom);


void desconectar_señal_btn      (GtkWidget **btn);

#endif
