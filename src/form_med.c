#include "form_med.h"
#include "general.h"

typedef struct {
  BaseForm baseVentana;
  EntradaTexto id;
  EntradaTexto substancia;
  EntradaTexto gramaje;
  EntradaTexto unidadesC;
  EntradaTexto presentacion;
  EntradaTexto lab;
  EntradaTexto costo;
  EntradaTexto lote;
  EntradaFecha caducidad;
  EntradaTexto unidadesI;
  EntradaTexto marca;
  GtkWidget *warningLbl;
  GtkWidget *aceptBtn;
  GtkWidget *cancelBtn;
} MedForm;

MedForm mForm;

void free_medform(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(mForm.baseVentana.win);
  if (!mForm.warningLbl)
    gtk_widget_destroy(mForm.warningLbl);
  if (!mForm.aceptBtn)
    gtk_widget_destroy(mForm.aceptBtn);
  if (!mForm.cancelBtn)
    gtk_widget_destroy(mForm.cancelBtn);

  free_entradatexto(&mForm.id);
  free_entradatexto(&mForm.substancia);
  free_entradatexto(&mForm.gramaje);
  free_entradatexto(&mForm.unidadesC);
  free_entradatexto(&mForm.presentacion);
  free_entradatexto(&mForm.lab);
  free_entradatexto(&mForm.costo);
  free_entradatexto(&mForm.lote);
  free_entradatexto(&mForm.unidadesI);
  free_entradatexto(&mForm.marca);

  free_entradafecha(&mForm.caducidad);

  free_baseform(&mForm.baseVentana);

  mForm.warningLbl = NULL;
  mForm.aceptBtn = NULL;
  mForm.cancelBtn = NULL;
}

void med_crear_form() {
  crear_ventana(&mForm.baseVentana, 611, 220, free_medform);

  crear_entradatexto(&mForm.id, "Clave", 10, 10);
  crear_entradatexto(&mForm.substancia, "Substancia", 10, 49);
  crear_entradatexto(&mForm.gramaje, "Gramaje", 7, 5);
  crear_entradatexto(&mForm.unidadesC, "Unidades\nCaja", 10, 10);
  crear_entradatexto(&mForm.presentacion, "Presentacion", 10, 49);
  crear_entradatexto(&mForm.lab, "Laboratorio", 10, 49);
  crear_entradatexto(&mForm.costo, "Costo", 7, 5);
  crear_entradatexto(&mForm.lote, "Lote", 5, 5);
  crear_entradatexto(&mForm.unidadesI, "Unidades\nInventario", 5, 5);
  crear_entradatexto(&mForm.marca, "Marca", 5, 49);

  crear_entradafecha(&mForm.caducidad, "Caducidad");

  mForm.warningLbl = gtk_label_new("");

  crear_boton(&mForm.aceptBtn, "Aceptar", NULL);
  crear_boton(&mForm.cancelBtn, "Cancelar", free_medform);

  // Clave
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.id.lbl, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.id.entry, 1, 0, 2, 1);

  // Substancia
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.substancia.lbl, 3, 0,
                  1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.substancia.entry, 4,
                  0, 3, 1);

  // Gramaje
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.gramaje.lbl, 0, 1, 1,
                  1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.gramaje.entry, 1, 1,
                  1, 1);

  // Cantidad / Unidades por caja
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesC.lbl, 2, 1,
                  1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesC.entry, 3, 1,
                  1, 1);

  // Presentación
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.presentacion.lbl, 4,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.presentacion.entry, 5,
                  1, 3, 1);

  // Laboratorio
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lab.lbl, 3, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lab.entry, 4, 4, 4,
                  1);

  // Costo
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.costo.lbl, 0, 3, 1,
                  1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.costo.entry, 1, 3, 1,
                  1);

  // Lote
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lote.lbl, 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lote.entry, 3, 3, 4,
                  1);

  // Caducidad
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.titulo, 7,
                  3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.anioEntry,
                  8, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.mesCombox,
                  9, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.diaCombox,
                  10, 3, 1, 1);

  // Unidades en inventario
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesI.lbl, 8, 1,
                  1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesI.entry, 9, 1,
                  2, 1);

  // Marca
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.marca.lbl, 7, 0, 1,
                  1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.marca.entry, 8, 0, 3,
                  1);

  // Warning
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.warningLbl, 1, 5, 9,
                  1);

  // Botones
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.aceptBtn, 1, 6, 4, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.cancelBtn, 6, 6, 4,
                  1);

  gtk_widget_show_all(mForm.baseVentana.win);
}
