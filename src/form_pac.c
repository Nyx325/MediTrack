#include "form_pac.h"
#include "general.h"

typedef struct {
  BaseForm basesVentana;
  EntradaTexto curp;
  EntradaTexto nombre;
  EntradaFecha fechaN;
  EntradaTexto telf;
  EntradaCombox tSangre;
  EntradaCombox sexo;
  EntradaFecha primCons;
  GtkWidget *warningLbl;
  GtkWidget *acepBtn;
  GtkWidget *cancelBtn;
} PacForm;

PacForm pForm;

Opc modo; //1 para modificar, 0 para agregar

void free_PacForm(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(pForm.basesVentana.win);

  if (pForm.acepBtn != NULL)
    gtk_widget_destroy(pForm.acepBtn);
  if (pForm.cancelBtn != NULL)
    gtk_widget_destroy(pForm.cancelBtn);

  free_entradatexto(&pForm.curp);
  free_entradatexto(&pForm.nombre);
  free_entradatexto(&pForm.telf);

  free_entradafecha(&pForm.primCons);
  free_entradafecha(&pForm.fechaN);

  free_entradacombox(&pForm.tSangre);
  free_entradacombox(&pForm.sexo);

  free_baseform(&pForm.basesVentana);

  pForm.warningLbl = NULL;
  pForm.acepBtn = NULL;
  pForm.cancelBtn = NULL;
}

void pac_crear_form() {
  crear_ventana(&pForm.basesVentana, 611, 220, free_PacForm);

  crear_entradatexto(&pForm.nombre, "Nombre", 49, 49);
  crear_entradatexto(&pForm.curp, "CURP", 18, 18);
  crear_entradatexto(&pForm.telf, "Teléfono", 10, 10);

  crear_entradafecha(&pForm.fechaN, "Fecha Nacimiento");
  crear_entradafecha(&pForm.primCons, "Primer Consulta");

  const gchar *sexoOpc[] = {"M", "H"};
  crear_entradacombox(&pForm.sexo, "Sexo", sexoOpc, G_N_ELEMENTS(sexoOpc));
  const gchar *tipos[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
  crear_entradacombox(&pForm.tSangre, "T. Sangre", tipos, G_N_ELEMENTS(tipos));

  pForm.warningLbl = gtk_label_new("");
  crear_boton(&pForm.acepBtn, "Aceptar", NULL);
  crear_boton(&pForm.cancelBtn, "Cancelar", free_PacForm);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.nombre.lbl, 0, 0, 2,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.nombre.entry, 2, 0,
                  3, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.curp.lbl, 5, 0, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.curp.entry, 6, 0, 2,
                  1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.titulo, 0, 1,
                  2, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.anioEntry, 2,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.mesCombox, 3,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.diaCombox, 4,
                  1, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.telf.lbl, 5, 1, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.telf.entry, 6, 1, 2,
                  1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.tSangre.lbl, 0, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.tSangre.combox, 1, 2,
                  1, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.sexo.lbl, 2, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.sexo.combox, 3, 2, 1,
                  1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.titulo, 4,
                  2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.anioEntry,
                  5, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.mesCombox,
                  6, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.diaCombox,
                  7, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.warningLbl, 0, 3, 8,
                  3);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.acepBtn, 0, 4, 4, 3);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.cancelBtn, 5, 4, 3,
                  3);

  // Cargar datos si es que es modificar(?) o cambiar una flag global aqui

  gtk_widget_show_all(pForm.basesVentana.win);
}


