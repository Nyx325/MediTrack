#include "form_pac.h"
#include "general.h"

typedef struct {
  GtkWidget *win;
  GtkWidget *grid;
  GdkPixbuf *icon;
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

void free_PacForm(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(pForm.win);
  if (pForm.win != NULL)
    gtk_widget_destroy(pForm.win);
  if (pForm.grid != NULL)
    gtk_widget_destroy(pForm.grid);
  if (pForm.icon != NULL)
    g_object_unref(pForm.icon);
  if (pForm.warningLbl != NULL)
    gtk_widget_destroy(pForm.warningLbl);
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

  pForm.win = NULL;
  pForm.grid = NULL;
  pForm.icon = NULL;
  pForm.warningLbl = NULL;
  pForm.acepBtn = NULL;
  pForm.cancelBtn = NULL;
}

void pac_crear_form() {
  pForm.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_default_size(GTK_WINDOW(pForm.win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(pForm.win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(pForm.win), 20);
  g_signal_connect(G_OBJECT(pForm.win), "destroy", G_CALLBACK(free_PacForm),
                   NULL);

  pForm.grid = gtk_grid_new();

  gtk_grid_set_row_spacing(GTK_GRID(pForm.grid), 20);
  gtk_grid_set_column_spacing(GTK_GRID(pForm.grid), 10);
  gtk_container_add(GTK_CONTAINER(pForm.win), pForm.grid);
  gtk_widget_set_halign(pForm.grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(pForm.grid, GTK_ALIGN_CENTER);

  pForm.icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(pForm.win), pForm.icon);

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
  crear_boton(&pForm.acepBtn, "Aceptar");
  crear_boton(&pForm.cancelBtn, "Cancelar");
  g_signal_connect(G_OBJECT(pForm.cancelBtn), "clicked",
                   G_CALLBACK(free_PacForm), NULL);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.nombre.lbl, 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.nombre.entry, 2, 0, 3, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.curp.lbl, 5, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.curp.entry, 6, 0, 2, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.fechaN.titulo, 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.fechaN.anioEntry, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.fechaN.mesCombox, 3, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.fechaN.diaCombox, 4, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.telf.lbl, 5, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.telf.entry, 6, 1, 2, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.tSangre.lbl, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.tSangre.combox, 1, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.sexo.lbl, 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.sexo.combox, 3, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.primCons.titulo, 4, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.primCons.anioEntry, 5, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.primCons.mesCombox, 6, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.primCons.diaCombox, 7, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.warningLbl, 0, 3, 8, 3);

  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.acepBtn, 0, 4, 4, 3);
  gtk_grid_attach(GTK_GRID(pForm.grid), pForm.cancelBtn, 5, 4, 3, 3);

  // Cargar datos si es que es modificar(?) o cambiar una flag global aqui

  gtk_widget_show_all(pForm.win);
}
