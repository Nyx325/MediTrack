#include "general.h"
#include <ctype.h>
#include <string.h>

// :D
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
// minúscula
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


void crear_entradatexto(EntradaTexto *info, char *titulo, int tamEntry,
                        int maxChars) {
  info->lbl = gtk_label_new(titulo);
  info->entry = gtk_entry_new();
  gtk_entry_set_width_chars(GTK_ENTRY(info->entry), tamEntry);
  gtk_entry_set_max_length(GTK_ENTRY(info->entry), maxChars);
}

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

void crear_entradacombox(EntradaCombox *entrada, char *titulo,
                         const gchar *datos[], int length) {
  entrada->lbl = gtk_label_new(titulo);
  entrada->combox = gtk_combo_box_text_new();

  for (int i = 0; i < length; i++)
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrada->combox),
                                   datos[i]);
}

void crear_boton(GtkWidget **btn, char *titulo) {
  *btn = gtk_button_new_with_label(titulo);
  GtkStyleContext *context;
  gtk_widget_set_name(*btn, "button");
  context = gtk_widget_get_style_context(*btn);
  gtk_style_context_add_class(context, "suggested-action");
}
