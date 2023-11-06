#include "form_pac.h"

gboolean opc; // indicar si está en modo modificar o agregar(?)
GtkWidget *fp_win, *fp_grid, *fp_combox[6], *fp_entry[5], *fp_btn[2],
    *fp_lbl[8];
GdkPixbuf *fp_icon;

void free_formpac() {}

void fp_wingrid() {
  fp_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // gtk_window_set_title(GTK_WINDOW(fp_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(fp_win), 750, 400);
  gtk_window_set_position(GTK_WINDOW(fp_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(fp_win), 20);
  // g_signal_connect(G_OBJECT(fp_win), "destroy", G_CALLBACK(gtk_main_quit),
  // NULL);

  fp_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(fp_grid),
                           20); // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(fp_grid),
                              10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(fp_win), fp_grid);

  fp_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(fp_win), fp_icon);
}

void init_lbl() {
  char *title[7] = {"Nombre", "CURP", "Fecha de Nacimiento", "Teléfono",
                    "Sangre", "Sexo", "Primera consulta"};
  int i;
  for (i = 0; i < 7; i++) {
    fp_lbl[i] = gtk_label_new(title[i]);
  }
}

void fp_init_entry() {
  int i;
  for (i = 0; i < 5; i++) {
    fp_entry[i] = gtk_entry_new();
  }
  for (i = 2; i < 5; i += 2) {
    gtk_entry_set_placeholder_text(GTK_ENTRY(fp_entry[i]), "Año");
  }
}

char dias_x_mes(const gint mes) {
  if (mes > 12 || mes < 1)
    return 0;

  if (mes == 2)
    return 29;

  if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 ||
      mes == 12)
    return 31;

  return 30;
}

void cambio_mes(GtkComboBox *widget, gpointer data) {
  GtkComboBoxText *dia_combox = GTK_COMBO_BOX_TEXT(data);
  gint active = gtk_combo_box_get_active(widget);

  gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(dia_combox));

  // Agregar la opción "Dia" como valor predeterminado
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(dia_combox), "Día");

  // Establecer "Dia" como el valor predeterminado
  gtk_combo_box_set_active(GTK_COMBO_BOX(dia_combox), 0);

  // Llenar el ComboBox con números del 1 al 12
  for (int i = 1; i <= dias_x_mes(active); i++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", i);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(dia_combox), buffer);
  }
}

void fp_gen_mescombox() {
  int i, j;
  for (i = 0; i < 5; i += 4) {
    fp_combox[i] = gtk_combo_box_text_new();
    fp_combox[i + 1] = gtk_combo_box_text_new();
    g_signal_connect(fp_combox[i], "changed", G_CALLBACK(cambio_mes),
                     fp_combox[i + 1]);

    // Agregar la opción "Mes" como valor predeterminado
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fp_combox[i]), "Mes");

    // Llenar el ComboBox con números del 1 al 12
    for (j = 1; j <= 12; j++) {
      char buffer[3];
      snprintf(buffer, sizeof(buffer), "%d", j);
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fp_combox[i]), buffer);
    }

    // Ahora, establecer "Mes" como el valor predeterminado después de llenar
    gtk_combo_box_set_active(GTK_COMBO_BOX(fp_combox[i]), 0);
  }
}

void fp_gen_tsangre() {
  int i;
  const gchar *tipos[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

  fp_combox[2] = gtk_combo_box_text_new();

  // agregar opción "Tipo"
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fp_combox[2]), "Tipo");
  // establecer "Tipo" como predeterminado
  gtk_combo_box_set_active(GTK_COMBO_BOX(fp_combox[2]), 0);

  // Llenar combobox
  for (i = 1; i <= G_N_ELEMENTS(tipos); i++)
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fp_combox[2]),
                                   tipos[i - 1]);
}

void fp_gen_sexo() {
  gchar *opc[] = {"M", "H"};

  fp_combox[3] = gtk_combo_box_text_new();

  for (char i = 0; i < G_N_ELEMENTS(opc); i++)
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fp_combox[3]), opc[i]);

  gtk_combo_box_set_active(GTK_COMBO_BOX(fp_combox[3]), 0);
}

void fp_gen_btns() {
  int i;
  char *title[2] = {"Aceptar", "Cancelar"};

  for (i = 0; i < 2; i++)
    fp_btn[i] = gtk_button_new_with_label(title[i]);
}

void fp_set_widgets() {
  // Nombre
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[0], 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[0], 2, 0, 3, 1);

  // CURP
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[1], 5, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[1], 6, 0, 2, 1);

  // Fecha de nacimiento
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[2], 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[2], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[0], 3, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[1], 4, 1, 1, 1);

  // Teléfono
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[3], 5, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[3], 6, 1, 2, 1);

  // Tipo de sangre
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[4], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[2], 1, 2, 1, 1);

  // Sexo
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[5], 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[3], 3, 2, 1, 1);

  // Primera consulta
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[6], 4, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[4], 5, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[3], 6, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[4], 6, 2, 1, 1);

  // colocar warning

  // botones
  gtk_grid_attach(GTK_GRID(fp_grid), fp_btn[0], 0, 4, 4, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_btn[1], 4, 4, 3, 1);
}

void gen_formpac() {
  fp_wingrid();
  init_lbl();
  fp_init_entry();
  fp_gen_mescombox();
  fp_gen_tsangre();
  fp_gen_sexo();
  fp_gen_btns();
  fp_set_widgets();

  gtk_widget_show_all(fp_win);
}
