#include "main.h"
#include "menu.h"

int main() {
  // Establecer la variable de entorno GTK_THEME con la ruta al tema descargado
  g_setenv("GTK_THEME", "../theme/gtk.css", TRUE);

  // Inicializar gtk
  gtk_init(NULL, NULL);

  // gen_login();
  // gen_menu();
  // pac_crear_form(1);
  // prov_crear_form(0);
  // listv_gen_table();
  crear_menu();

  gtk_main();
  return 0;
}
