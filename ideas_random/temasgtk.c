#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
  // Inicializar GTK
  gtk_init(&argc, &argv);

  // Crear una ventana
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

  // Crear un botón
  GtkWidget *button = gtk_button_new_with_label("Botón");

  // Establecer una clase CSS al botón
  gtk_widget_set_name(button, "my-button");

  // Crear un contenedor y agregar el botón
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_add(GTK_CONTAINER(box), button);
  gtk_container_set_border_width(GTK_CONTAINER(box), 10);
  gtk_container_add(GTK_CONTAINER(window), box);

  // Cargar el archivo CSS del tema
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "../theme/gtk.css", NULL);

  // Aplicar el CSS al botón y a la ventana
  GtkStyleContext *context = gtk_widget_get_style_context(button);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                 GTK_STYLE_PROVIDER_PRIORITY_USER);

  context = gtk_widget_get_style_context(window);
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                 GTK_STYLE_PROVIDER_PRIORITY_USER);

  // Mostrar la ventana y el botón
  gtk_widget_show_all(window);

  // Ejecutar el bucle principal de GTK
  gtk_main();

  return 0;
}
