#include "form_pac.h"

gboolean fp_opc; // indicar si está en modo modificar o agregar(?)
GtkWidget *fp_win, *fp_grid, *fp_combox[6], *fp_entry[5], *fp_btn[2],
    *fp_lbl[8];
GdkPixbuf *fp_icon;

gboolean fp_reset_warning(GtkWidget *widget, GdkEventButton *event, gpointer data) {
  gtk_label_set_text(GTK_LABEL(fp_lbl[7]), NULL);
  return FALSE;
}

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
  gtk_grid_set_row_spacing(GTK_GRID(fp_grid), 20); // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(fp_grid), 10); // Espaciado horizontal
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
    g_signal_connect(G_OBJECT(fp_entry[i]), "button-press-event", G_CALLBACK(fp_reset_warning), NULL);
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

  g_signal_connect(G_OBJECT(fp_btn[0]), "clicked", G_CALLBACK(aceptar_opc),
                   NULL);
  g_signal_connect(G_OBJECT(fp_btn[1]), "clicked", G_CALLBACK(free_formpac),
                   NULL);
}

void fp_set_widgets() {
  // Nombre
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[0], 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_entry[0], 2, 0, 3, 1);
  gtk_entry_set_max_length(GTK_ENTRY(fp_entry[0]), 50);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[0]), 50);

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
  // gtk_entry_set_max_length(GTK_ENTRY(fp_entry[2]), 18);
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
  // gtk_entry_set_max_length(GTK_ENTRY(fp_entry[4]), 18);
  gtk_entry_set_width_chars(GTK_ENTRY(fp_entry[4]), 4);

  // colocar warning

  // botones
  gtk_grid_attach(GTK_GRID(fp_grid), fp_btn[0], 0, 4, 4, 3);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_btn[1], 5, 4, 3, 3);
}

void gen_warning(){
  fp_lbl[7] = gtk_label_new(NULL);
  gtk_grid_attach(GTK_GRID(fp_grid), fp_lbl[7], 0, 3, 7, 1);
}
/*
void fp_show_warning(){
  gtk_label_set_markup(GTK_LABEL(log_warning), "<span foreground='red'>Usuario o contraseña incorrectos</span>");
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

gchar *formatear_nombre(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gboolean flag = TRUE;
  gchar *formateo = g_strdup(input); // Copia la cadena de entrada
  gunichar character;

  if (tam == 0)
    return NULL;

  for (gsize i = 0; i < tam; i++) {
    character = g_utf8_get_char(&formateo[i]);

    if (!g_unichar_isspace(character) && !g_unichar_isalpha(character))
      return NULL;

    if (flag) {
      // Volver mayúscula la primera letra de la palabra
      formateo[i] = g_unichar_totitle(character);
      flag = FALSE;
    } else {
      // Convierte el resto de las letras a minúsculas
      formateo[i] = g_unichar_tolower(character);
    }

    if (g_unichar_isspace(character))
      flag = TRUE;
  }

  return formateo;
}

gchar *formatear_curp(const char *input) {
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

  return formateo;
}

gchar *formatear_full_nums(const gchar *input, gsize max_tam, gsize min_tam) {
  const gsize tam = g_utf8_strlen(input, -1);
  gsize i;
  gchar *formateo = g_strdup(input);
  gunichar character;

  if (max_tam != -1 && tam > max_tam)
    return NULL;

  if (min_tam != -1 && tam < min_tam)
    return NULL;

  for (i = 0; i < tam; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isdigit(character))
      return NULL;
    else
      formateo[i] = character;
  }

  return formateo;
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

void aceptar_opc(GtkWidget *wid, gpointer data) {
  const gchar *input[4], *tsangre;
  gchar *output[4];
  gunichar sexo;
  GString *err = g_string_new("");
  int cboxf_output[4];
  char i;

  // VALIDACIONES
  //  Obtener nombre
  input[0] = gtk_entry_get_text(GTK_ENTRY(fp_entry[0]));
  // validar
  output[0] = formatear_nombre(input[0]);

  if (!output[0])
    agregar_err("Nombre", &err);

  // Obtener curp
  input[1] = gtk_entry_get_text(GTK_ENTRY(fp_entry[1]));
  // validar
  output[1] = formatear_curp(input[1]);

  if (!output[1])
    agregar_err("CURP", &err);

  // Obtener año
  input[2] = gtk_entry_get_text(GTK_ENTRY(fp_entry[2]));
  // validar
  output[2] = formatear_full_nums(input[2], -1, 1);
  if (!output[2])
    agregar_err("Año de nacimiento", &err);

  cboxf_output[0] = gtk_combo_box_get_active(GTK_COMBO_BOX(fp_combox[0]));
  if (cboxf_output[0] == 0)
    agregar_err("Mes de nacimiento", &err);

  cboxf_output[1] = gtk_combo_box_get_active(GTK_COMBO_BOX(fp_combox[1]));
  if (cboxf_output[1] == 0)
    agregar_err("Dia de nacimiento", &err);

  // NO TIENE UN FILTRO DE MIN NUMS
  input[3] = gtk_entry_get_text(GTK_ENTRY(fp_entry[3]));
  // validar
  output[3] = formatear_full_nums(input[3], 10, 10);
  if (!output[3])
    agregar_err("Teléfono", &err);

  tsangre = formatear_tsangre(GTK_COMBO_BOX(fp_combox[2]));
  if (tsangre == NULL)
    agregar_err("Tipo de sangre", &err);

  sexo = formatear_sexo(GTK_COMBO_BOX_TEXT(fp_combox[3]));

  if (err->len != 0) {
    g_string_append(err, " no válido(s)");
    gtk_label_set_markup(GTK_LABEL(fp_lbl[7]), err->str);
  } else{
    // llamar a función de esribir supongo
    free_formpac();
  }
 

  // liberar todo
  //g_print("%s\n", err->str);
  g_string_free(err, TRUE);

  for (i = 0; i < 4; i++) {
    g_free(output[i]);
  }
}
