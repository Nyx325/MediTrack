#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *m_btn_img =
      gtk_image_new_from_file("../images/medicinas_menu2.jpeg");
  GtkWidget *btn = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(btn), m_btn_img);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_destroy(m_btn_img);

  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}
