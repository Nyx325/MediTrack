#include "form_consul.h"

GtkWidget *c_win, *c_grid, *c_entry[9], *c_lbl[12], *c_combox[2], *c_btn[2],
    *c_txtview[3], *c_scrolled_window[3], *c_frame[3], *c_separator;

GdkPixbuf *c_icon;

void free_formcons() {
  short i;
  gtk_widget_hide(c_win);
  // Si el apuntador != NULL, liberar
  if (c_icon) {
    g_object_unref(c_icon);
    c_icon = NULL;
  }
  for (i = 0; i < 9; i++) {
    if (c_entry[i]) {
      gtk_widget_destroy(c_entry[i]);
      c_entry[i] = NULL;
    }
  }
  for (i = 0; i < 12; i++) {
    if (c_lbl[i]) {
      gtk_widget_destroy(c_lbl[i]);
      c_lbl[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (c_combox[i]) {
      gtk_widget_destroy(c_combox[i]);
      c_combox[i] = NULL;
    }
    if (c_btn[i]) {
      gtk_widget_destroy(c_btn[i]);
      c_btn[i] = NULL;
    }
  }
  for (i = 0; i < 3; i++) {
    if (c_txtview[i]) {
      gtk_widget_destroy(c_txtview[i]);
      c_txtview[i] = NULL;
    }
    if (c_scrolled_window[i]) {
      gtk_widget_destroy(c_scrolled_window[i]);
      c_scrolled_window[i] = NULL;
    }
  }
  if (c_grid) {
    gtk_widget_destroy(c_win);
    c_win = NULL;
  }
  if (c_win) {
    gtk_widget_destroy(c_win);
    c_win = NULL;
  }
}

void c_wingrid() {
  // Crear ventana
  c_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Configurar tamaño, posición, padding y envento de cerrado
  //  gtk_window_set_title(GTK_WINDOW(p_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(c_win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(c_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(c_win), 20);
  g_signal_connect(G_OBJECT(c_win), "destroy", G_CALLBACK(free_formcons), NULL);

  // Crear grid principal
  c_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(c_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(c_grid), 10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(c_win), c_grid);
  gtk_widget_set_halign(c_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(c_grid, GTK_ALIGN_CENTER);

  // Generar icono
  c_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(c_win), c_icon);

  c_separator = gtk_label_new("");
}

void c_init_lbl() {
  short i;
  char *titulos[] = {"Nombre",
                     "Fecha",
                     "Edad",
                     "Peso",
                     "Altura",
                     "Doctor(a)",
                     "Presión",
                     "T °C",
                     "Sintomas",
                     "Alergias",
                     "Enfermedades crónicas",
                     " "};

  for (i = 0; i < 12; i++)
    c_lbl[i] = gtk_label_new(titulos[i]);
}

void c_init_entry() {
  short i;

  for (i = 0; i < 9; i++)
    c_entry[i] = gtk_entry_new();

  // Colocar texto "Año" al entry de fecha
  gtk_entry_set_placeholder_text(GTK_ENTRY(c_entry[1]), "Año");
  gtk_entry_set_placeholder_text(GTK_ENTRY(c_entry[6]), "Sist");
  gtk_entry_set_placeholder_text(GTK_ENTRY(c_entry[7]), "Diast");
}

void c_init_combox() {
  short j;

  for (j = 0; j < 2; j++)
    c_combox[j] = gtk_combo_box_text_new();

  // Hacer que el contenido de la box de dias dependa del mes elegido
  g_signal_connect(c_combox[0], "changed", G_CALLBACK(cambio_mes), c_combox[1]);

  // Agregar la opción "Mes"
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(c_combox[0]), "Mes");

  // Llenar el ComboBox con números del 1 al 12
  for (j = 1; j <= 12; j++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", j);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(c_combox[0]), buffer);
  }

  // Ahora, establecer "Mes" como el valor predeterminado después de llenar
  gtk_combo_box_set_active(GTK_COMBO_BOX(c_combox[0]), 0);
}

void c_init_btn() {
  GtkStyleContext *context;
  short i;
  char *titulos[] = {"Aceptar", "Cancelar"};

  for (i = 0; i < 2; i++) {
    c_btn[i] = gtk_button_new_with_label(titulos[i]);
    // Agregar nombre de objeto en el CSS
    gtk_widget_set_name(c_btn[i], "button");
    // Agregar clase
    context = gtk_widget_get_style_context(c_btn[i]);
    gtk_style_context_add_class(context, "suggested-action");
  }
}

void c_init_txtview() {
  short i;
  for (i = 0; i < 3; i++) {
    c_txtview[i] = gtk_text_view_new();

    c_scrolled_window[i] = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(c_scrolled_window[i]), c_txtview[i]);

    c_frame[i] = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(c_frame[i]), c_scrolled_window[i]);
    gtk_frame_set_shadow_type(GTK_FRAME(c_frame[i]), GTK_SHADOW_IN);
  }

  // gtk_widget_set_size_request(scrolled_window, 200, 100);
}

void c_set_widgets() {
  // Nombre Paciente
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[0], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[0], 1, 0, 5, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_separator, 6, 0, 4, 1);
  // gtk_entry_set_width_chars(GTK_ENTRY(c_separator), 30);
  // gtk_entry_set_max_length(GTK_ENTRY(c_entry[0]), 30);
  // gtk_entry_set_width_chars(GTK_ENTRY(c_entry[0]), 30);

  // Fecha
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[1], 10, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[1], 11, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_combox[0], 12, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_combox[1], 13, 0, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[1]), 4);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[1]), 4);

  // Edad
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[2], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[2], 1, 1, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[2]), 3);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[2]), 2);

  // Peso
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[3], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[3], 3, 1, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[3]), 3);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[3]), 3);

  // Altura
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[4], 4, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[4], 5, 1, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[4]), 4);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[4]), 3);

  // Doctor
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[5], 9, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[5], 10, 1, 4, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(c_entry[4]), 4);
  // gtk_entry_set_width_chars(GTK_ENTRY(c_entry[4]), 3);

  // Presión
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[6], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[6], 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[7], 2, 2, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[6]), 4);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[6]), 4);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[7]), 4);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[7]), 5);

  // Temperatura
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[7], 3, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_entry[8], 4, 2, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(c_entry[8]), 3);
  gtk_entry_set_width_chars(GTK_ENTRY(c_entry[8]), 2);

  // Síntomas
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[8], 0, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_frame[0], 0, 4, 9, 11);

  // Alergias
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[9], 10, 3, 2, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_frame[1], 10, 4, 5, 5);

  // Alergias
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[10], 10, 9, 2, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_frame[2], 10, 10, 5, 5);

  // Alerta
  gtk_grid_attach(GTK_GRID(c_grid), c_lbl[11], 0, 16, 1, 1);

  // Botones
  gtk_grid_attach(GTK_GRID(c_grid), c_btn[0], 0, 17, 9, 1);
  gtk_grid_attach(GTK_GRID(c_grid), c_btn[1], 10, 17, 6, 1);
}

void gen_formcons() {
  // Inicializar widgets
  c_wingrid();
  c_init_lbl();
  c_init_entry();
  c_init_combox();
  c_init_btn();
  c_init_txtview();
  // Colocar widgets en la ventana
  c_set_widgets();

  gtk_widget_show_all(c_win);
}
