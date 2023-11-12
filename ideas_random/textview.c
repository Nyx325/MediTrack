#include <gtk/gtk.h>

// Función para obtener el contenido del GtkTextView
char *get_text_from_textview(GtkTextView *textview) {
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  char *result = g_strdup(text);
  g_free(text);
  return result;
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *scrolled_window;
  GtkWidget *text_view;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  text_view = gtk_text_view_new();

  gtk_widget_set_size_request(scrolled_window, 200, 100);
  gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
  gtk_container_add(GTK_CONTAINER(window), scrolled_window);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
