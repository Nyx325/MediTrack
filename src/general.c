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
