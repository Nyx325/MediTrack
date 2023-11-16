#include <gtk/gtk.h>

GtkWidget *p_btn[2];

void p_init_btn() {
  short i;
  char *titulos[] = {"Aceptar", "Cancelar"};

  for (i = 0; i < 2; i++) {
    p_btn[i] = gtk_button_new_with_label(titulos[i]);

    // Obtener el contexto de estilo del botón
    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(p_btn[i]));

    // Agregar la clase de estilo "green-button" al contexto de estilo
    gtk_style_context_add_class(context, "green-button");
  }
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // Crear una ventana principal
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  // Crear un grid para los botones
  GtkWidget *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  // Inicializar los botones
  p_init_btn();

  // Agregar los botones al grid
  for (int i = 0; i < 2; i++) {
    gtk_grid_attach(GTK_GRID(grid), p_btn[i], i, 0, 1, 1);
  }

  // Cargar el archivo CSS
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "../theme/style.css", NULL);

  // Aplicar el proveedor de CSS a la pantalla principal
  GdkDisplay *display = gdk_display_get_default();
  GdkScreen *screen = gdk_display_get_default_screen(display);
  gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  // Mostrar la ventana principal y ejecutar el bucle principal de GTK
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
