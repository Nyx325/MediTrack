#include <gtk/gtk.h>

typedef struct {
  GtkWidget *text_view;
  GtkTextBuffer *buffer;
  GtkLabel *char_count_label;
  int maxChars;
} TextvConBuff;

void contador_chars(GtkWidget *btn, gpointer data) {
  TextvConBuff *entrada = (TextvConBuff *)data;
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(entrada->buffer, &start);
  gtk_text_buffer_get_end_iter(entrada->buffer, &end);
  gchar *text = gtk_text_buffer_get_text(entrada->buffer, &start, &end, FALSE);
  long cEscritos = g_utf8_strlen(text, -1);
  g_free(text);

  char count_str[50 + 35];

  if (cEscritos < entrada->maxChars) {
    snprintf(count_str, sizeof(count_str), "%ld/%d", cEscritos,
             entrada->maxChars);
    gtk_label_set_text(GTK_LABEL(entrada->char_count_label), count_str);
  } else {
    snprintf(
        count_str, sizeof(count_str),
        "%ld/%d\nTexto demasiado largo, NO serán guardados todos los datos",
        cEscritos, entrada->maxChars);
    gtk_label_set_text(GTK_LABEL(entrada->char_count_label), count_str);
  }
}

TextvConBuff crear_textview(int maxChars) {
  TextvConBuff entrada;
  entrada.buffer = gtk_text_buffer_new(NULL);
  entrada.text_view = gtk_text_view_new_with_buffer(entrada.buffer);
  entrada.char_count_label = GTK_LABEL(gtk_label_new(""));
  entrada.maxChars = maxChars;

  // Connect the "changed" signal to update the character count

  return entrada;
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  TextvConBuff textv = crear_textview(10);
  g_signal_connect(G_OBJECT(textv.buffer), "changed",
                   G_CALLBACK(contador_chars), &textv);
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(vbox), textv.text_view);
  gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(textv.char_count_label));

  gtk_container_add(GTK_CONTAINER(window), vbox);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
