#include "form_med.h"

GtkWidget *fm_win, *fm_grid, *fm_lbl[12], *fm_entry[12], *fm_combox[2],
    *fm_btn[2];
GdkPixbuf *fm_icon;

void free_formed() {
  short i;
  gtk_widget_hide(fm_win);
  if (fm_icon) {
    g_object_unref(fm_icon);
    fm_icon = NULL;
  }
  for (i = 0; i < 12; i++) {
    if (fm_lbl[i]) {
      gtk_widget_destroy(fm_lbl[i]);
      fm_lbl[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (fm_combox[i]) {
      gtk_widget_destroy(fm_combox[i]);
      fm_combox[i] = NULL;
    }
  }
  for (i = 0; i < 12; i++) {
    if (fm_entry[i]) {
      gtk_widget_destroy(fm_entry[i]);
      fm_entry[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (fm_btn[i]) {
      gtk_widget_destroy(fm_btn[i]);
      fm_btn[i] = NULL;
    }
  }
  if (fm_grid) {
    gtk_widget_destroy(fm_grid);
    fm_grid = NULL;
  }
  if (fm_win) {
    gtk_widget_destroy(fm_win);
    fm_win = NULL;
  }
}

void fm_wingrid() {
  fm_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // gtk_window_set_title(GTK_WINDOW(fm_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(fm_win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(fm_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(fm_win), 20);
  g_signal_connect(G_OBJECT(fm_win), "destroy", G_CALLBACK(free_formed), NULL);

  fm_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(fm_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(fm_grid), 10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(fm_win), fm_grid);
  gtk_widget_set_halign(fm_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(fm_grid, GTK_ALIGN_CENTER);

  fm_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(fm_win), fm_icon);
}

// Crear los apuntadores a los label y les coloca el texto
void fm_init_lbl() {
  char *fm_titles[] = {"Clave",
                       "Substancia",
                       "Marca",
                       "Gramaje",
                       "Cantidad",
                       "Presentación",
                       "Laboratorio",
                       "Costo",
                       "Lote",
                       "Caducidad",
                       "Unidades en inventario",
                       " "};
  short i;

  for (i = 0; i < 12; i++)
    fm_lbl[i] = gtk_label_new(fm_titles[i]);
}

void fm_init_entry() {
  short i;
  for (i = 0; i < 12; i++)
    fm_entry[i] = gtk_entry_new();

  // Colocar al entry para la fecha el texto
  gtk_entry_set_placeholder_text(GTK_ENTRY(fm_entry[9]), "Año");
}

void fm_init_combox() {
  short j;
  for (j = 0; j < 2; j++)
    fm_combox[j] = gtk_combo_box_text_new();

  // Hacer que el contenido de la box de dias dependa del mes elegido
  g_signal_connect(fm_combox[0], "changed", G_CALLBACK(cambio_mes),
                   fm_combox[1]);

  // Agregar la opción "Mes"
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fm_combox[0]), "Mes");

  // Llenar el ComboBox con números del 1 al 12
  for (j = 1; j <= 12; j++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", j);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fm_combox[0]), buffer);
  }

  // Ahora, establecer "Mes" como el valor predeterminado después de llenar
  gtk_combo_box_set_active(GTK_COMBO_BOX(fm_combox[0]), 0);
}

void fm_init_btn() {
  GtkStyleContext *context;
  short i;
  char *title[] = {"Aceptar", "Cancelar"};

  for (i = 0; i < 2; i++) {
    fm_btn[i] = gtk_button_new_with_label(title[i]);
    // Agregar nombre de objeto en el CSS
    gtk_widget_set_name(fm_btn[i], "button");
    // Agregar clase
    context = gtk_widget_get_style_context(fm_btn[i]);
    gtk_style_context_add_class(context, "suggested-action");
  }
}

void fm_Set_widgets() {
  // Clave
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[0], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[0], 1, 0, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[0]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[0]), 30);

  // Substancia
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[1], 3, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[1], 5, 0, 3, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[1]), 50);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[1]), 50);

  // Marca
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[2], 8, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[2], 9, 0, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[2]), 18);
  // gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[2]), 18);

  // Gramaje
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[3], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[3], 1, 1, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[3]), 18);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[3]), 5);

  // Cantidad
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[4], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[4], 3, 1, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[4]), 18);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[4]), 3);

  // Presentación
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[5], 4, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[5], 5, 1, 3, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[1]), 18);
  // gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[1]), 18);

  // Laboratorio
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[6], 8, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[6], 9, 1, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[1]), 18);
  // gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[1]), 18);

  // Costo
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[7], 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[7], 1, 3, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[7]), 18);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[7]), 5);

  // Lote
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[8], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[8], 3, 3, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[8]), 20);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[8]), 20);

  // Caducidad
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[9], 5, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[9], 6, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_combox[0], 7, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_combox[1], 8, 3, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[9]), 5);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[9]), 5);

  // Unidades en inventario
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[10], 9, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[10], 10, 3, 1, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(fm_entry[9]), 18);
  // gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[9]), 18);

  // Warning
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[11], 1, 5, 1, 1);

  // Botones
  gtk_grid_attach(GTK_GRID(fm_grid), fm_btn[0], 0, 6, 4, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_btn[1], 5, 6, 3, 1);
}

void gen_formed() {
  // Generar ventana
  fm_wingrid();
  // Incializar widgets
  fm_init_lbl();
  fm_init_entry();
  fm_init_combox();
  fm_init_btn();
  // Distribuir en la ventana
  fm_Set_widgets();

  gtk_widget_show_all(fm_win);
}
