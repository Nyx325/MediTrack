#ifndef GENERAL_H
#define GENERAL_H

#include <gtk/gtk.h>

void        cambio_mes                  (GtkComboBox *widget, gpointer data);
char        dias_x_mes                  (const gint mes);
char        *formatear_nombre           (const gchar *input);
gboolean    is_full_nums                (const gchar *input, gsize max_tam, gsize min_tam);
gboolean    es_vocal_acentuada          (char c);
char        *formatear_num              (const gchar *input, gsize max_tam, gsize min_tam);

#endif
