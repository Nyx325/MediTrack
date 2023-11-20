#include <gtk/gtk.h>

static void on_combo_changed(GtkComboBox *combo, gpointer user_data) {
  GtkTreeModel *model = gtk_combo_box_get_model(combo);
  GtkTreeIter iter;

  if (gtk_combo_box_get_active_iter(combo, &iter)) {
    gchar *selected_value;
    gtk_tree_model_get(model, &iter, 0, &selected_value, -1);
    g_print("Opción seleccionada: %s\n", selected_value);
    g_free(selected_value);
  }
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // Crear una ventana principal
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "ComboBox en GTK");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 300, 100);

  // Crear un ComboBox
  GtkWidget *combo = gtk_combo_box_text_new();

  // Agregar la opción "Hola" como valor predeterminado
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Hola");

  // Llenar el ComboBox con números del 1 al 12
  for (int i = 1; i <= 12; i++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", i);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), buffer);
  }

  // Establecer "Hola" como el valor predeterminado
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

  // Agregar el ComboBox a la ventana
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), combo, TRUE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // Conectar la señal de cierre de la ventana
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);
  g_signal_connect(combo, "changed", G_CALLBACK(on_combo_changed), NULL);

  // Mostrar todo
  gtk_widget_show_all(window);

  // Iniciar el bucle principal de GTK
  gtk_main();

  return 0;
}
