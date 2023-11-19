#include "general.h"

typedef struct {
  GtkWidget *win;
  GtkWidget *grid;
  GdkPixbuf *icon;
  EntradaTexto nomComercial;
  EntradaTexto NomFactura;
  EntradaTexto rfc;
  EntradaTexto numOficina;
  EntradaTexto wsp;
  EntradaTexto correo;
  EntradaTexto repComercial;
  EntradaTexto domicilio;
  GtkWidget *narcoticosLbl;
  GtkWidget *narcoticosCheckBtn;
  EntradaFecha vigenciaPersmiso;
  GtkWidget *warningLbl;
  GtkWidget *aceptBtn;
  GtkWidget *cancelBtn;
} FormProv;

FormProv prForm;

void free_provform(GtkWidget *widget, gpointer data){
    gtk_widget_hide(prForm.win);
}
