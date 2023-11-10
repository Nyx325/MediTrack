#include "form_prov.h"

GtkWidget *p_win, *p_grid, *p_entry[8], *p_lbl[9], *p_combox[2], *p_btn[2],
    *p_checkbtn;
GdkPixbuf *p_icon;

// Elimina y libera memoria de todos los objetos
// de la ventana del formulario de proveedores
void free_formprov() {
  short i;
  gtk_widget_hide(p_win);
  // Si el apuntador != NULL, liberar
  if (p_icon) {
    g_object_unref(p_icon);
    p_icon = NULL;
  }
  for (i = 0; i < 8; i++) {
    if (p_entry[i]) {
      gtk_widget_destroy(p_entry[i]);
      p_entry[i] = NULL;
    }
  }
  for (i = 0; i < 9; i++) {
    if (p_lbl[i]) {
      gtk_widget_destroy(p_lbl[i]);
      p_lbl[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (p_combox[i]) {
      gtk_widget_destroy(p_combox[i]);
      p_combox[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (p_btn[i]) {
      gtk_widget_destroy(p_btn[i]);
      p_btn[i] = NULL;
    }
  }
  if (p_checkbtn) {
    gtk_widget_destroy(p_checkbtn);
    p_checkbtn = NULL;
  }
  if (p_grid) {
    gtk_widget_destroy(p_win);
    p_win = NULL;
  }
  if (p_win) {
    gtk_widget_destroy(p_win);
    p_win = NULL;
  }
}

void p_wingrid() {

  // Crear ventana
  p_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Configurar tamaño, posición, padding y envento de cerrado
  //  gtk_window_set_title(GTK_WINDOW(p_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(p_win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(p_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(p_win), 20);
  g_signal_connect(G_OBJECT(p_win), "destroy", G_CALLBACK(free_formprov), NULL);

  // Crear grid principal
  p_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(p_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(p_grid), 10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(p_win), p_grid);

  // Generar icono
  p_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(p_win), p_icon);
}

// Crear los apuntadores a los label y les coloca el texto
void p_init_lbl() {
  short i;
  char *titulos[] = {"Nombre comercial",        "Nombre de factura", "RFC",
                     "Núm. oficina",       "Whatsapp",          "Correo",
                     "Representante Comercial", "Vigencia",          " "};

  for (i = 0; i < 9; i++)
    p_lbl[i] = gtk_label_new(titulos[i]);
}

void p_init_entry() {
  short i;

  for (i = 0; i < 8; i++)
    p_entry[i] = gtk_entry_new();

  // Colocar texto "Año" al entry de fecha
  gtk_entry_set_placeholder_text(GTK_ENTRY(p_entry[7]), "Año");
}

void p_init_combox() {
  short j;

  for (j = 0; j < 2; j++)
    p_combox[j] = gtk_combo_box_text_new();

  // Hacer que el contenido de la box de dias dependa del mes elegido
  g_signal_connect(p_combox[0], "changed", G_CALLBACK(cambio_mes), p_combox[1]);

  // Agregar la opción "Mes"
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(p_combox[0]), "Mes");

  // Llenar el ComboBox con números del 1 al 12
  for (j = 1; j <= 12; j++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", j);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(p_combox[0]), buffer);
  }

  // Ahora, establecer "Mes" como el valor predeterminado después de llenar
  gtk_combo_box_set_active(GTK_COMBO_BOX(p_combox[0]), 0);
}

void p_init_btn() {
  short i;
  char *titulos[] = {"Aceptar", "Cancelar"};

  for (i = 0; i < 2; i++)
    p_btn[i] = gtk_button_new_with_label(titulos[i]);
}

void on_check_button_toggled(GtkWidget *widget, gpointer data) {
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
    g_print("Checkbox está seleccionado\n");
  } else {
    g_print("Checkbox no está seleccionado\n");
  }
}

void p_init_checkbtn() {
  p_checkbtn =
      gtk_check_button_new_with_label("Permiso de venta\nde narcóticos");
  g_signal_connect(p_checkbtn, "toggled", G_CALLBACK(on_check_button_toggled),
                   NULL);
}

void p_set_widgets() {
  // Nombre comercial
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[0], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[0], 1, 0, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[0]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[0]), 30);

  // Nombre Factura
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[1], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[1], 1, 1, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[1]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[1]), 30);

  // RFC
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[2], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[2], 1, 2, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[1]), 15);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[1]), 15);

  // Número de oficina
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[3], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[3], 3, 3, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[3]), 10);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[3]), 10);

  // Whatsapp
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[4], 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[4], 1, 3, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(p_entry[3]), 30);
  // gtk_entry_set_width_chars(GTK_ENTRY(p_entry[3]), 30);

  // Correo
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[5], 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[5], 3, 2, 2, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(p_entry[4]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[4]), 20);

  // Representante comercial
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[6], 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[6], 1, 4, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[6]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[6]), 30);

  // Permiso venta narcóticos
  gtk_grid_attach(GTK_GRID(p_grid), p_checkbtn, 0, 5, 1, 1);

  // Vigencia
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[7], 1, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[7], 2, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_combox[0], 3, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_combox[1], 4, 5, 1, 1);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[7]), 4);

  //Botones
  gtk_grid_attach(GTK_GRID(p_grid), p_btn[0], 0, 7, 2, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_btn[1], 2, 7, 3, 1);
}

void gen_formprov() {
  // Generar ventana
  p_wingrid();
  // Incializar widgets
  p_init_lbl();
  p_init_entry();
  p_init_checkbtn();
  p_init_combox();
  p_init_btn();
  // Distribuir en la ventana
  p_set_widgets();

  gtk_widget_show_all(p_win);
}
