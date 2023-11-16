#include "form_med.h"
#include "general.h"
#include "listv.h"
#include <stdio.h>

GtkWidget *fm_win, *fm_grid, *fm_lbl[12], *fm_entry[11], *fm_combox[2],
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
                       "Gramaje (g)",
                       "Cantidad",
                       "Presentación",
                       "Laboratorio",
                       "Costo",
                       "Lote",
                       "Caducidad",
                       "Unidades en\ninventario",
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
  g_signal_connect(G_OBJECT(fm_btn[0]), "clicked", G_CALLBACK(fm_aceptar),
                   NULL);
  g_signal_connect(G_OBJECT(fm_btn[1]), "clicked", G_CALLBACK(free_formed),
                   NULL);
}

void fm_Set_widgets() {
  // Clave
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[0], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[0], 1, 0, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[0]), 10);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[0]), 10);

  // Substancia
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[1], 3, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[1], 4, 0, 3, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[1]), 49);
  // gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[1]), 49);

  // Gramaje
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[3], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[3], 1, 1, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[3]), 7);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[3]), 5);

  // Cantidad / Unidades por caja
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[4], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[4], 3, 1, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[4]), 10);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[4]), 10);

  // Presentación
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[5], 4, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[5], 5, 1, 3, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[1]), 50);

  // Laboratorio
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[6], 3, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[6], 4, 4, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[1]), 49);

  // Costo
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[7], 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[7], 1, 3, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[7]), 7);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[7]), 5);

  // Lote
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[8], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[8], 3, 3, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[8]), 20);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[8]), 20);

  // Caducidad
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[9], 7, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[9], 8, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_combox[0], 9, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_combox[1], 10, 3, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[9]), 5);
  gtk_entry_set_width_chars(GTK_ENTRY(fm_entry[9]), 5);

  // Unidades en inventario
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[10], 8, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[10], 9, 1, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[0]), 10);

  // Marca
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[2], 7, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_entry[2], 8, 0, 3, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fm_entry[2]), 49);

  // Warning
  gtk_grid_attach(GTK_GRID(fm_grid), fm_lbl[11], 1, 5, 1, 1);

  // Botones
  gtk_grid_attach(GTK_GRID(fm_grid), fm_btn[0], 1, 6, 4, 1);
  gtk_grid_attach(GTK_GRID(fm_grid), fm_btn[1], 6, 6, 4, 1);
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

void fm_aceptar(GtkWidget *wid, gpointer data) {
  GString *err = g_string_new("");
  Medicamento registroM;
  const char *input[11];
  char *output[3];
  FILE *apArch;
  ushort i;
  registroM.estado = 0;

  // Clave del medicamento
  input[0] = gtk_entry_get_text(GTK_ENTRY(fm_entry[0]));
  if (!is_full_nums(input[0], -1, -1))
    agregar_err("Clave", &err);
  else
    registroM.id = atoi(input[0]);

  // Substancia
  input[1] = gtk_entry_get_text(GTK_ENTRY(fm_entry[1]));
  output[0] = formatear_nombre(input[1]);
  if (output[0] == NULL)
    agregar_err("Substancia", &err);
  else
    strcpy(registroM.sustancia, output[0]);

  // Marca
  input[2] = gtk_entry_get_text(GTK_ENTRY(fm_entry[2]));
  // Sólo copiamos la cadena porque no necesitamos formato
  output[1] = g_strdup(input[2]);
  // Si el input está vacío
  if (output[1][0] == '\0')
    agregar_err("Marca", &err);
  else
    strcpy(registroM.marca, output[1]);

  // Gramaje
  input[3] = gtk_entry_get_text(GTK_ENTRY(fm_entry[3]));
  if (!is_number(input[3], -1, -1))
    agregar_err("Gramaje", &err);
  else
    registroM.gramaje = atof(input[3]);

  // Cantidad / Unidades x caja
  input[4] = gtk_entry_get_text(GTK_ENTRY(fm_entry[4]));
  g_print("%s\n", input[4]);
  if (!is_full_nums(input[4], -1, -1))
    agregar_err("Cantidad por caja", &err);
  else
    registroM.unidadesCaja = atoi(input[4]);

  // Presentacion
  input[5] = gtk_entry_get_text(GTK_ENTRY(fm_entry[5]));
  output[2] = formatear_nombre(input[5]);
  if (output[2] == NULL)
    agregar_err("Presentación", &err);
  else
    strcpy(registroM.presentacion, output[2]);

  // Unidades en inventario
  input[10] = gtk_entry_get_text(GTK_ENTRY(fm_entry[10]));
  if (!is_full_nums(input[10], -1, -1))
    agregar_err("Unidades en inventario", &err);
  else
    registroM.unidadesInventario = atoi(input[10]);

  // Costo
  input[7] = gtk_entry_get_text(GTK_ENTRY(fm_entry[7]));
  if (!is_number(input[7], -1, -1))
    agregar_err("Costo", &err);
  else
    registroM.costo = atof(input[7]);

  // Lote
  input[8] = gtk_entry_get_text(GTK_ENTRY(fm_entry[8]));
  // Si cadena vacía
  if (g_utf8_strlen(input[8], -1) == 0)
    agregar_err("Lote", &err);
  else
    strcpy(registroM.lote, input[8]);

  // Caducidad
  // Año
  input[9] = gtk_entry_get_text(GTK_ENTRY(fm_entry[9]));
  if (!is_full_nums(input[9], -1, -1))
    agregar_err("Año de caducidad", &err);
  else
    registroM.fecha.anio = atoi(input[9]);

  // Mes
  registroM.fecha.mes = gtk_combo_box_get_active(GTK_COMBO_BOX(fm_combox[0]));
  if (registroM.fecha.mes == 0)
    agregar_err("Mes de caducidad", &err);

  // Dia
  registroM.fecha.dia = gtk_combo_box_get_active(GTK_COMBO_BOX(fm_combox[1]));
  if (registroM.fecha.dia == 0)
    agregar_err("Dia de caducidad", &err);

  // Laboratorio
  input[6] = gtk_entry_get_text(GTK_ENTRY(fm_entry[6]));
  // Si cadena vacía
  if (g_utf8_strlen(input[6], -1) == 0)
    agregar_err("Laboratorio", &err);
  else
    strcpy(registroM.laboratorio, input[6]);

  if (err->len == 0) {
    registroM.estado = 1;
    free_formed();
    agregarMedicamento("../data/medicamentos.dat", registroM);
    mostrarMed("../data/medicamentos.dat");
  } else
    agregar_err("no válido(s)", &err);
  g_print("%s\n", err->str);
  g_string_free(err, TRUE);
  for (i = 0; i < 3; i++)
    if (output[i])
      g_free(output[i]);
}

int agregarMedicamento(char *archivoDir, Medicamento registro) {
  FILE *apArch = fopen(archivoDir, "ab");
  if (apArch == NULL) {
    g_print("Archivo dañado\n");
    return 0;
  }

  fwrite(&registro, sizeof(Medicamento), 1, apArch);
  fclose(apArch);
  return 1;
}

void mostrarMed(char nomMed[]) {
  unsigned long pos;
  Medicamento med;
  char fechaFormato[12];
  GtkTreeIter iter;
  FILE *apArch;

  // Eliminar todos los elementos del ListStore
  if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(lv_lstore), &iter))
    gtk_list_store_clear(lv_lstore);

  // apuntador definido en listv.c para el modelo de la tabla
  lv_lstore = gtk_list_store_new(12, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_FLOAT, G_TYPE_UINT, G_TYPE_STRING,
                                 G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_STRING,
                                 G_TYPE_STRING, G_TYPE_STRING, G_TYPE_ULONG);

  apArch = fopen(nomMed, "a+b");
  if (apArch == NULL) {
    g_print("Archivo dañado");
    return;
  }

  while (fread(&med, sizeof(Medicamento), 1, apArch)) {
    if (med.estado) {
      pos = (unsigned long)ftell(apArch);
      // Formatear fecha como cadena
      sprintf(fechaFormato, "%02d/%02d/%04d", med.fecha.dia, med.fecha.mes,
              med.fecha.anio);
      // Agregar fila
      gtk_list_store_append(lv_lstore, &iter);
      // Agregar datos al modelo
      gtk_list_store_set(lv_lstore, &iter, 0, med.id, 1, med.sustancia, 2,
                         med.marca, 3, med.gramaje, 4, med.unidadesCaja, 5,
                         med.presentacion, 6, med.unidadesInventario, 7,
                         med.costo, 8, med.lote, 9, fechaFormato, 10,
                         med.laboratorio, 11, pos, -1);
    }
  }
  fclose(apArch);
  char *titulos[] = {"Clave",
                     "Substancia",
                     "Marca",
                     "Gramaje (g)",
                     "Cantidad",
                     "Presentacion",
                     "Unidades de inventario",
                     "Costo",
                     "Lote",
                     "Caducidad",
                     "Laboratorio"};
  lv_importmodel(11, titulos);
}
