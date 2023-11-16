#include "general.h"

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

gboolean reset_warning(GtkWidget *widget, GdkEventButton *event,
                       gpointer data) {
  gtk_label_set_text(GTK_LABEL(data), NULL);
  return FALSE;
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

char *formatear_nombre(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gboolean flag = TRUE;
  gchar *formateo = g_strdup(input);

  if (tam == 0)
    return NULL;

  for (gsize i = 0; i < tam; i++) {
    gunichar2 character = g_utf8_get_char(formateo + i);

    if (g_unichar_iscntrl(character)) {
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

char *formatear_num(const gchar *input, gsize max_tam, gsize min_tam) {
  if (is_full_nums(input, max_tam, min_tam) == FALSE)
    return NULL;

  return g_strdup(input);
}

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

void agregar_err(char *texto, GString **cadena) {
  if ((*cadena)->len == 0) {
    g_string_append(*cadena, texto);
  } else {
    g_string_append(*cadena, ", ");
    g_string_append(*cadena, texto);
  }
}
