#include "form_pac.h"
#include "general.h"
#include "listv.h"
#include <stdio.h>

gboolean fp_opc; // indicar si está en modo modificar o agregar(?)
GtkWidget *fp_win, *fp_grid, *fp_combox[6], *fp_entry[5], *fp_btn[2],
    *fp_lbl[8];
GdkPixbuf *fp_icon;

void free_formpac() {
  gtk_widget_hide(fp_win);
  if (fp_icon) {
    g_object_unref(fp_icon);
    fp_icon = NULL;
  }
  for (int i = 0; i < 8; i++) {
    if (fp_lbl[i]) {
      gtk_widget_destroy(fp_lbl[i]);
      fp_lbl[i] = NULL;
    }
  }
  for (int i = 0; i < 6; i++) {
    if (fp_combox[i]) {
      gtk_widget_destroy(fp_combox[i]);
      fp_combox[i] = NULL;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (fp_entry[i]) {
      gtk_widget_destroy(fp_entry[i]);
      fp_entry[i] = NULL;
    }
  }
  for (int i = 0; i < 2; i++) {
    if (fp_btn[i]) {
      gtk_widget_destroy(fp_btn[i]);
      fp_btn[i] = NULL;
    }
  }
  if (fp_grid) {
    gtk_widget_destroy(fp_grid);
    fp_grid = NULL;
  }
  if (fp_win) {
    gtk_widget_destroy(fp_win);
    fp_win = NULL;
  }
}

void fp_wingrid() {
  fp_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // gtk_window_set_title(GTK_WINDOW(fp_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(fp_win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(fp_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(fp_win), 20);
  g_signal_connect(G_OBJECT(fp_win), "destroy", G_CALLBACK(free_formpac), NULL);

  fp_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(fp_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(fp_grid), 10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(fp_win), fp_grid);
  gtk_widget_set_halign(fp_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(fp_grid, GTK_ALIGN_CENTER);

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
    g_signal_connect(G_OBJECT(fp_entry[i]), "button-press-event",
                     G_CALLBACK(reset_warning), fp_lbl[7]);
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
  GtkStyleContext *context;
  int i;
  char *title[2] = {"Aceptar", "Cancelar"};

  for (i = 0; i < 2; i++) {
    fp_btn[i] = gtk_button_new_with_label(title[i]);
    gtk_widget_set_name(fp_btn[i], "button");
    context = gtk_widget_get_style_context(fp_btn[i]);
    gtk_style_context_add_class(context, "suggested-action");
  }

  g_signal_connect(G_OBJECT(fp_btn[0]), "clicked", G_CALLBACK(fp_aceptar),
                   NULL);
  g_signal_connect(G_OBJECT(fp_btn[1]), "clicked", G_CALLBACK(free_formpac),
                   NULL);
}

void fp_set_widgets() {
  // Nombre
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[0], 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[0], 2, 0, 3, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fp_entry[0]), 49);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[0]), 49);

  // CURP
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[1], 5, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[1], 6, 0, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fp_entry[1]), 18);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[1]), 18);

  // Fecha de nacimiento
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[2], 0, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[2], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[0], 3, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[1], 4, 1, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fp_entry[2]), 4);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[2]), 4);

  // Teléfono
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[3], 5, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[3], 6, 1, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fp_entry[3]), 10);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[3]), 10);

  // Tipo de sangre
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[4], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[2], 1, 2, 1, 1);

  // Sexo
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[5], 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[3], 3, 2, 1, 1);

  // Primera consulta
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[6], 4, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[4], 5, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[4], 6, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_combox[5], 7, 2, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fp_entry[4]), 4);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[4]), 4);

  // colocar warning

  // botones
  gtk_grid_attach(GTK_GRID(fp_grid), fp_btn[0], 0, 4, 4, 3);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_btn[1], 5, 4, 3, 3);
}

void gen_warning() {
  fp_lbl[7] = gtk_label_new(NULL);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[7], 0, 3, 7, 1);
}
/*
void fp_show_warning(){
  gtk_label_set_markup(GTK_LABEL(log_warning), "<span foreground='red'>Usuario o
contraseña incorrectos</span>");
}
*/

void gen_formpac() {
  fp_wingrid();
  init_lbl();
  fp_init_entry();
  fp_gen_mescombox();
  fp_gen_tsangre();
  fp_gen_sexo();
  gen_warning();
  fp_gen_btns();
  fp_set_widgets();

  gtk_widget_show_all(fp_win);
}

// Validaciones
void agregar_err(char *texto, GString **cadena) {
  if ((*cadena)->len == 0) {
    g_string_append(*cadena, texto);
  } else {
    g_string_append(*cadena, ", ");
    g_string_append(*cadena, texto);
  }
}

char *formatear_curp(const char *input) {
  gsize i, tam = g_utf8_strlen(input, -1);
  gchar *formateo = g_strdup(input); // Copia la cadena de entrada
  gunichar character;

  if (tam != 18)
    return NULL;

  for (i = 0; i < 4; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isalpha(character))
      return NULL;
    else
      formateo[i] = g_unichar_totitle(character);
  }

  for (i = 4; i < 10; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isdigit(character))
      return NULL;
    else
      formateo[i] = character;
  }

  for (i = 10; i < tam; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isalnum(character))
      return NULL;

    if (g_unichar_isalpha(character))
      formateo[i] = g_unichar_totitle(character);
    else
      formateo[i] = character;
  }

  return g_strdup(formateo);
}

const gchar *formatear_tsangre(GtkComboBox *combox) {
  int ind = gtk_combo_box_get_active(GTK_COMBO_BOX(combox));
  switch (ind) {
  case 0:
    return NULL;
  case 1:
    return "A+";
  case 2:
    return "A-";
  case 3:
    return "B+";
  case 4:
    return "B-";
  case 5:
    return "AB+";
  case 6:
    return "AB-";
  case 7:
    return "O+";
  case 8:
    return "O-";
  default:
    return NULL;
  }
}

gunichar formatear_sexo(GtkComboBoxText *combox) {
  gchar *formateo = gtk_combo_box_text_get_active_text(combox);
  gunichar sexo = g_utf8_get_char(&formateo[0]);
  return sexo;
}

void fp_aceptar(GtkWidget *wid, gpointer data) {
  Pacientes registroP;
  const gchar *input[6], *tsangre;
  char *output[3];
  gunichar sexo;
  GString *err = g_string_new("");
  int cboxf_output[4];
  char i;

  registroP.estado = 0;

  // VALIDACIONES
  //  Obtener nombre
  input[0] = gtk_entry_get_text(GTK_ENTRY(fp_entry[0]));
  // validar
  output[0] = formatear_nombre(input[0]);
  if (output[0] == NULL)
    agregar_err("Nombre", &err);
  else
    strcpy(registroP.nombre, output[0]);

  // Obtener curp
  input[1] = gtk_entry_get_text(GTK_ENTRY(fp_entry[1]));
  // validar
  output[1] = formatear_curp(input[1]);
  if (output[1] == NULL)
    agregar_err("CURP", &err);
  else
    strcpy(registroP.CURP, output[1]);

  // Obtener año
  input[2] = gtk_entry_get_text(GTK_ENTRY(fp_entry[2]));
  if (is_full_nums(input[2], -1, 1) == FALSE)
    agregar_err("Año de nacimiento", &err);
  else
    registroP.fechas.anio = atoi(input[2]);

  // Obtener mes
  registroP.fechas.mes = gtk_combo_box_get_active(GTK_COMBO_BOX(fp_combox[0]));
  if (registroP.fechas.mes == 0)
    agregar_err("Mes de nacimiento", &err);

  // Obtener dia
  registroP.fechas.dia = gtk_combo_box_get_active(GTK_COMBO_BOX(fp_combox[1]));
  if (registroP.fechas.dia == 0)
    agregar_err("Dia de nacimiento", &err);

  // Obtener telefono
  input[3] = gtk_entry_get_text(GTK_ENTRY(fp_entry[3]));
  if (is_full_nums(input[3], -1, 10) == FALSE)
    agregar_err("Teléfono", &err);
  else
    strcpy(registroP.telf, input[3]);

  input[4] = formatear_tsangre(GTK_COMBO_BOX(fp_combox[2]));
  if (input[4] == NULL)
    agregar_err("Tipo de sangre", &err);
  else
    strcpy(registroP.tpSangre, input[4]);

  registroP.sexo = formatear_sexo(GTK_COMBO_BOX_TEXT(fp_combox[3]));

  // Primer conculsta
  // Obtener año
  input[5] = gtk_entry_get_text(GTK_ENTRY(fp_entry[4]));
  if (is_full_nums(input[5], -1, 1) == FALSE)
    agregar_err("Año de primer consulta", &err);
  else
    registroP.fechasC.anio = atoi(input[5]);

  // Obtener mes
  registroP.fechasC.mes = gtk_combo_box_get_active(GTK_COMBO_BOX(fp_combox[4]));
  if (registroP.fechasC.mes == 0)
    agregar_err("Mes de nacimiento", &err);

  // Obtener dia
  registroP.fechasC.dia = gtk_combo_box_get_active(GTK_COMBO_BOX(fp_combox[5]));
  if (registroP.fechasC.dia == 0)
    agregar_err("Dia de nacimiento", &err);

  // Si algún campo no es válido
  if (err->len != 0) {
    g_string_append(err, " no válido(s)");
    gtk_label_set_markup(GTK_LABEL(fp_lbl[7]), err->str);
  } else {
    registroP.estado = 1;
    addPaciente("../data/pacientes.dat", registroP);
    free_formpac();

    gtk_list_store_clear(lv_lstore);
    mostrarPaci("../data/pacientes.dat");
  }

  // liberar todo
  // g_print("%s\n", err->str);
  g_string_free(err, TRUE);
  for (i = 0; i < 2; i++) {
    if (output[i])
      g_free(output[i]);
  }
}

int addPaciente(char nomPac[], Pacientes paciente) {
  FILE *apPaci;

  apPaci = fopen(nomPac, "ab");
  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return 0;
  }

  fwrite(&paciente, sizeof(Pacientes), 1, apPaci);
  fclose(apPaci);
  return 1;
}

void mostrarPaci(char nomPac[]) {
  char fechaFormato[2][12];
  GtkTreeIter iter; // estructura para identificar fila en modelo
  // apuntador definido en listv.c para el modelo de la tabla
  lv_lstore = gtk_list_store_new(8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_STRING, G_TYPE_ULONG);

  FILE *apPaci;
  Pacientes paciente;

  apPaci = fopen(nomPac, "a+b");
  if (apPaci == NULL) {
    printf("Archivo danaño\n");
    return;
  }
  // fseek(apPaci,0,SEEK_SET);

  // fread(&paciente, sizeof(Pacientes), 1, apPaci);
  unsigned long pos;

  while (fread(&paciente, sizeof(Pacientes), 1, apPaci)) {
    if (paciente.estado) {
      // Formatear la fecha almacenada en una cadena para mostrarla en la tabla
      sprintf(fechaFormato[0], "%02d/%02d/%04d", paciente.fechas.dia,
              paciente.fechas.mes, paciente.fechas.anio);
      sprintf(fechaFormato[1], "%02d/%02d/%04d", paciente.fechasC.dia,
              paciente.fechasC.mes, paciente.fechasC.anio);
      // Formatear el sexo de igual forma
      char sexo[2] = {paciente.sexo, '\0'};

      // Obtener posición en archivo del registro
      pos = (unsigned long)ftell(apPaci) - sizeof(Pacientes);

      gtk_list_store_append(lv_lstore, &iter); // agregar fila nueva
      // Agregar datos al modelo
      gtk_list_store_set(lv_lstore, &iter, 0, paciente.CURP, 1, paciente.nombre,
                         2, fechaFormato[0], 3, sexo, 4, paciente.telf, 5,
                         paciente.tpSangre, 6, fechaFormato[1], 7, pos, -1);
    }
  }
  fclose(apPaci);

  char *titulos[] = {
      "CURP",     "Nombre",         "Fecha de nacimineto",  "Sexo",
      "Teléfono", "Tipo sanguineo", "Fecha primer consulta"};
  lv_importmodel(7, titulos);
}
