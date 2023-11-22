#include "general.h"
#include <ctype.h>
#include <string.h>

void no_callback(GtkWidget *widget, gpointer data) {}

// Retorno de el número de dias máximos según el mes
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

// Vacía un entry, que posiblemente se trate de las advertencias de los
// formularios
gboolean reset_warning(GtkWidget *widget, GdkEventButton *event,
                       gpointer data) {
  gtk_label_set_text(GTK_LABEL(data), NULL);
  return FALSE;
}

// Establece el contenido de un combo box de Día dado el mes elegido
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

// Formatea una cadena con primer letra de cada palabra mayúscula y el resto
// minúscula, no admite números
char *formatear_nombre(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gboolean flag = TRUE;
  gchar *formateo = g_strdup(input);

  if (tam == 0) {
    g_free(formateo);
    return NULL;
  }

  for (gsize i = 0; i < tam; i++) {
    gunichar2 character = g_utf8_get_char(formateo + i);

    if (g_unichar_isdigit(character)) {
      g_free(formateo);
      return NULL;
    }

    if (flag) {
      // Volver mayúscula la primera letra de la palabra
      formateo[i] = g_unichar_toupper(character);
      flag = FALSE;
    } else {
      // Convierte el resto de las letras a minúsculas
      formateo[i] = g_unichar_tolower(character);
    }

    if (g_unichar_isspace(character))
      flag = TRUE;
  }

  return g_strdup(formateo);
}

// Formatea una cadena con primer letra de cada palabra mayúscula y el resto
// minúscula, admite números
char *formatear_palabra(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gboolean inicioPalabra = TRUE;
  gchar *formateo = g_strdup(input);

  if (tam == 0) {
    g_free(formateo);
    return NULL;
  }

  for (gsize i = 0; i < tam; i++) {
    gunichar2 character = g_utf8_get_char(formateo + i);

    if (inicioPalabra == TRUE && !g_unichar_isdigit(character)) {
      formateo[i] = g_unichar_toupper(character);
      inicioPalabra = FALSE;
    } else if (inicioPalabra == FALSE && !g_unichar_isdigit(character))
      formateo[i] = g_unichar_tolower(character);
    else
      formateo[i] = character;

    if (g_unichar_isspace(character))
      inicioPalabra = TRUE;
  }

  return g_strdup(formateo);
}

// Comprueba si una cadena está compuesta unicamente por números
gboolean is_full_nums(const gchar *input, gsize max_tam, gsize min_tam) {
  const gsize tam = g_utf8_strlen(input, -1);
  gsize i;
  gunichar character;

  if (max_tam != -1 && tam > max_tam)
    return FALSE;

  if (min_tam != -1 && tam < min_tam)
    return FALSE;

  for (i = 0; i < tam; i++) {
    character = g_utf8_get_char(&input[i]);
    if (!g_unichar_isdigit(character))
      return FALSE;
  }

  return TRUE;
}

// Compara si la cadena contiene un número, por lo que compara si tiene
// números y '.'
gboolean is_number(const gchar *input, gsize max_tam, gsize min_tam) {
  const gsize tam = g_utf8_strlen(input, -1);
  gsize i;
  gunichar character;

  if (max_tam != -1 && tam > max_tam)
    return FALSE;

  if (min_tam != -1 && tam < min_tam)
    return FALSE;

  for (i = 0; i < tam; i++) {
    character = g_utf8_get_char(&input[i]);
    if (!g_unichar_isdigit(character) && character != '.')
      return FALSE;
  }

  return TRUE;
}

// Comprueba que una cadena sea completamente de números y que su largo
// mínimo y máximo sea de 10 después lo convierte a char*
char *formatear_telf(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gchar *formateo = g_strdup(input);

  if (tam == 0) {
    g_free(formateo);
    return NULL;
  }

  if (is_full_nums(input, 10, 10) == FALSE) {
    g_free(formateo);
    return NULL;
  }

  return g_strdup(formateo);
}

// Recibe una cadena que debe convertirse en un número ya sea flotante o entero,
// verifica que sea un número válido
char *formatear_num(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gchar *formateo = g_strdup(input);

  if (tam == 0) {
    g_free(formateo);
    return NULL;
  }

  if (is_number(input, 9, -1) == FALSE) {
    g_free(formateo);
    return NULL;
  }

  return g_strdup(formateo);
}

// Dado lv_lstore inicializado con datos dentro genera la tabla de cada
// categoría
void import_model(GtkWidget *tview, GtkListStore *model, unsigned short numCols,
                  char *titulos[]) {
  unsigned short i;
  tview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));

  for (i = 0; i < numCols; i++) {
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    GtkCellRenderer *render = gtk_cell_renderer_text_new();
    gtk_tree_view_column_set_title(column, titulos[i]);
    gtk_tree_view_column_pack_start(column, render, TRUE);
    gtk_tree_view_column_add_attribute(column, render, "text", i);
    // Configurar el tamaño de las columnas
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    // Ajustar propiedades para expandir
    gtk_tree_view_column_set_expand(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tview), column);
  }
}

// Dada una cadena GString agrega como listado las cadenas que se mandan como
// argumento
void agregar_err(char *texto, GString **cadena) {
  if ((*cadena)->len == 0) {
    g_string_append(*cadena, texto);
  } else {
    g_string_append(*cadena, ", ");
    g_string_append(*cadena, texto);
  }
}

void free_entradatexto(EntradaTexto *entrada) {
  if (entrada == NULL)
    return;

  if (entrada->lbl != NULL)
    gtk_widget_destroy(entrada->lbl);

  if (entrada->entry != NULL)
    gtk_widget_destroy(entrada->entry);

  entrada->lbl = NULL;
  entrada->entry = NULL;
}

void free_entradafecha(EntradaFecha *fecha) {
  if (fecha == NULL)
    return;

  if (fecha->anioEntry != NULL)
    gtk_widget_destroy(fecha->anioEntry);

  if (fecha->mesCombox != NULL)
    gtk_widget_destroy(fecha->mesCombox);

  if (fecha->diaCombox != NULL)
    gtk_widget_destroy(fecha->diaCombox);

  if (fecha->titulo != NULL)
    gtk_widget_destroy(fecha->titulo);

  fecha->anioEntry = NULL;
  fecha->mesCombox = NULL;
  fecha->diaCombox = NULL;
  fecha->titulo = NULL;
}

void free_entradacombox(EntradaCombox *entrada) {
  if (entrada == NULL)
    return;

  if (entrada->lbl != NULL)
    gtk_widget_destroy(entrada->lbl);

  if (entrada->combox != NULL)
    gtk_widget_destroy(entrada->combox);

  entrada->lbl = NULL;
  entrada->combox = NULL;
}

void free_baseform(BaseForm *basesVentana) {
  if (basesVentana == NULL)
    return;

  if (basesVentana->icon != NULL)
    g_object_unref(basesVentana->icon);
  if (basesVentana->grid != NULL)
    gtk_widget_destroy(basesVentana->grid);
  // if (basesVentana->win != NULL)
  //   gtk_widget_destroy(basesVentana->win);

  basesVentana->icon = NULL;
  basesVentana->grid = NULL;
  basesVentana->win = NULL;
}

// Crea un entry y un label para un apartado de texto, se agrega el tamaño del
// entry y caracteres máximos, además titulo del label
void crear_entradatexto(EntradaTexto *info, char *titulo, int tamEntry,
                        int maxChars) {
  info->lbl = gtk_label_new(titulo);
  info->entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(info->entry), tamEntry);
  gtk_entry_set_max_length(GTK_ENTRY(info->entry), maxChars);
}

// Crea un label, un entry y dos combo box que corresponden a dia, mes y año
void crear_entradafecha(EntradaFecha *fecha, char *titulo) {
  char j;
  fecha->titulo = gtk_label_new(titulo);

  fecha->anioEntry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(fecha->anioEntry), 4);
  gtk_entry_set_max_length(GTK_ENTRY(fecha->anioEntry), 4);
  gtk_entry_set_placeholder_text(GTK_ENTRY(fecha->anioEntry), "Año");

  fecha->mesCombox = gtk_combo_box_text_new();
  fecha->diaCombox = gtk_combo_box_text_new();

  // Hacer que el valor del día dependa del mes elegido
  g_signal_connect(fecha->mesCombox, "changed", G_CALLBACK(cambio_mes),
                   fecha->diaCombox);

  // Agregar la opción "Mes" como valor predeterminado
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fecha->mesCombox), "Mes");
  gtk_combo_box_set_active(GTK_COMBO_BOX(fecha->mesCombox), 0);

  // Llenar el ComboBox con números del 1 al 12
  for (j = 1; j <= 12; j++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", j);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fecha->mesCombox),
                                   buffer);
  }
}

// Crea un label y un combobox, recibe como arreglo de cadenas las opciones
// que se agregan, así como el numero de opciones
void crear_entradacombox(EntradaCombox *entrada, char *titulo,
                         const gchar *datos[], int length) {
  entrada->lbl = gtk_label_new(titulo);
  entrada->combox = gtk_combo_box_text_new();

  for (int i = 0; i < length; i++)
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrada->combox),
                                   datos[i]);
}

// Crea un botón con titulo, además recibe la función que llamará cuando se
// presione
void crear_boton(GtkWidget **btn, char *titulo, CallbackFunc callback) {
  *btn = gtk_button_new_with_label(titulo);
  GtkStyleContext *context;
  gtk_widget_set_name(*btn, "button");
  context = gtk_widget_get_style_context(*btn);
  gtk_style_context_add_class(context, "suggested-action");
  g_signal_connect(G_OBJECT(*btn), "clicked", G_CALLBACK(callback), NULL);
}

void crear_ventana(BaseForm *baseDelFormulario, int xRes, int yRes,
                   CallbackFunc callback) {

  baseDelFormulario->win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_default_size(GTK_WINDOW(baseDelFormulario->win), xRes, yRes);
  gtk_window_set_position(GTK_WINDOW(baseDelFormulario->win),
                          GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(baseDelFormulario->win), 20);
  if (callback != NULL)
    g_signal_connect(G_OBJECT(baseDelFormulario->win), "destroy",
                     G_CALLBACK(callback), NULL);

  baseDelFormulario->grid = gtk_grid_new();

  gtk_grid_set_row_spacing(GTK_GRID(baseDelFormulario->grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(baseDelFormulario->grid), 10);
  gtk_container_add(GTK_CONTAINER(baseDelFormulario->win),
                    baseDelFormulario->grid);
  gtk_widget_set_halign(baseDelFormulario->grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(baseDelFormulario->grid, GTK_ALIGN_CENTER);

  baseDelFormulario->icon =
      gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(baseDelFormulario->win),
                      baseDelFormulario->icon);
}

int formatear_tsangre_num(char *tipoS) {
  if (strcmp(tipoS, "A+") == 0)
    return 1;
  if (strcmp(tipoS, "A-") == 0)
    return 2;
  if (strcmp(tipoS, "B+") == 0)
    return 3;
  if (strcmp(tipoS, "B-") == 0)
    return 4;
  if (strcmp(tipoS, "AB+") == 0)
    return 5;
  if (strcmp(tipoS, "AB-") == 0)
    return 6;
  if (strcmp(tipoS, "O+") == 0)
    return 7;
  if (strcmp(tipoS, "O-") == 0)
    return 8;

  return 0;
}

void free_basebtn(BtnBase *bBtn) {
  if (bBtn->img != NULL)
    gtk_widget_destroy(bBtn->img);
  if (bBtn->btn != NULL)
    gtk_widget_destroy(bBtn->btn);

  bBtn->img = NULL;
  bBtn->btn = NULL;
}

void crear_btn_img(BtnBase *btn, char *imgPath) {
  btn->btn = gtk_button_new();
  btn->img = gtk_image_new_from_file(imgPath);
  gtk_button_set_image(GTK_BUTTON(btn->btn), btn->img);
}

// Puntero a una función que retorna un array y recibe un array tipo gchar
typedef char *(*FuncFormato)(const gchar *);

void capturar_formatear_texto(TextoIngresado *dato, char *registro,
                              FuncFormato funcion, GtkWidget *entry,
                              GString **err, char *errNom) {
  dato->textoEntry = gtk_entry_get_text(GTK_ENTRY(entry));
  dato->entradaFormato = funcion(dato->textoEntry);
  if (dato->entradaFormato == NULL)
    agregar_err(errNom, err);
  else
    strcpy(registro, dato->entradaFormato);

  g_free(dato->entradaFormato);
}

void capturar_formatear_fecha(FechaIngresada *fecha, WidgetsFecha *widgets,
                              Fecha *fechaReg, GString **err, char *errNom) {
  char buffer[20] = "";

  fecha->anio = gtk_entry_get_text(widgets->anioEntry);
  if (is_full_nums(fecha->anio, 4, 4) == FALSE) {
    snprintf(buffer, sizeof(buffer), "Año %s", errNom);
    agregar_err(errNom, err);
  } else
    fechaReg->anio = atoi(fecha->anio);

  g_print("%s\n", buffer);

  fechaReg->mes = gtk_combo_box_get_active(widgets->mesCombox);
  if (fechaReg->mes == 0) {
    snprintf(buffer, sizeof(buffer), "Mes %s", errNom);
    agregar_err(errNom, err);
  }

  g_print("%s\n", buffer);

  fechaReg->dia = gtk_combo_box_get_active(widgets->diaCombox);
  if (fechaReg->dia == 0) {
    snprintf(buffer, sizeof(buffer), "Dia %s", errNom);
    agregar_err(errNom, err);
  }
}

void desconectar_señal_btn(GtkWidget **btn) {
  if (*btn != NULL)
    g_signal_handlers_disconnect_matched(G_OBJECT(*btn), G_SIGNAL_MATCH_DATA, 0,
                                         0, NULL, NULL, NULL);
}

void imprimir_paciente(Pacientes p) {
  g_print("Estado: %d Nombre: %s Curp: %s\n", p.estado, p.nombre, p.CURP);
  g_print("FechaN: %d/%d/%d ", p.fechas.dia, p.fechas.mes, p.fechas.anio);
  g_print("Sexo %c Tel: %s\n", p.sexo, p.telf);
  g_print("T. Sangre %s ", p.tpSangre);
  g_print("FechaC: %d/%d/%d\n", p.fechasC.dia, p.fechasC.mes, p.fechasC.anio);
}

gboolean gchar_a_char(gchar *cadenaOrigen, char *cadenaDestino) {
  char *cadenaConvertida = g_strdup(cadenaOrigen);
  strcpy(cadenaDestino, cadenaConvertida);

  g_free(cadenaConvertida);
  return TRUE;
}

gboolean fechaGchar_a_int(gchar *entrada, Fecha *salida) {
  if (sscanf(entrada, "%d/%d/%d", &salida->dia, &salida->mes, &salida->anio) !=
      3) {
    g_print("ERROR: No se pudo formatear fecha\n\n");
    return FALSE;
  }
  return TRUE;
}

void gchar_a_int(gchar *entrada, int *dato) {
  char *cadenaSinFromato = g_strdup(entrada);
  *dato = atoi(cadenaSinFromato);
  g_free(cadenaSinFromato);
}

gboolean gchar_a_uint(gchar *cadena, unsigned int *resultado) {
  char *cadenaConvertida = g_strdup(cadena);

  // Intenta convertir la cadena a unsigned long
  char *endptr;
  unsigned long valorUnsignedLong = strtoul(cadenaConvertida, &endptr, 10);

  // Verifica si la conversión fue exitosa
  if (*endptr == '\0') {
    *resultado = (unsigned int)valorUnsignedLong;
    g_free(cadenaConvertida);
    return TRUE;
  }

  g_free(cadenaConvertida);
  return FALSE;
}

/*
gboolean carpeta_existe(const char *dirCarpeta) {
#ifdef _WIN32
  DWORD attrib = GetFileAttributesA(dirCarpeta);
  if (attrib != INVALID_FILE_ATTRIBUTES &&
      (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
    return TRUE; // Carpeta existe en Windows
  } else {
    if (_mkdir(dirCarpeta) == 0) {
      return TRUE; // Carpeta creada exitosamente en Windows
    } else {
      perror("Error al crear la carpeta");
      return FALSE; // Error al crear la carpeta en Windows
    }
  }
#else
  struct stat st;
  if (stat(dirCarpeta, &st) == 0) {
    if (S_ISDIR(st.st_mode)) {
      return TRUE; // Carpeta existe en Linux
    } else {
      printf("La ruta existe pero no es una carpeta en Linux.\n");
      return FALSE; // No es una carpeta en Linux
    }
  } else {
    if (mkdir(dirCarpeta, 0777) == 0) {
      return TRUE; // Carpeta creada exitosamente en Linux
    } else {
      perror("Error al crear la carpeta");
      return FALSE; // Error al crear la carpeta en Linux
    }
  }
#endif
}

void preparar_carpetas() {
#ifdef _WIN32
  if (carpeta_existe("..\\data\\"))
    if (!carpeta_existe("..\\data\\consultas"))
      exit(1);
#else
  if (carpeta_existe("../data/"))
    if (!carpeta_existe("../data/consultas"))
      exit(1);
#endif
}
*/
/*
gboolean preparar_archivos() {
#ifdef _WIN32
  if (!GetFileAttributesA("..\\data\\usr") != INVALID_FILE_ATTRIBUTES) {
  FILE *apArch
  
#else

#endif
}
*/
