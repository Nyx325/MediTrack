#include "main.h"
#include "form_med.h"

int main() {
  // Establecer la variable de entorno GTK_THEME con la ruta al tema descargado
  g_setenv("GTK_THEME", "../theme/gtk.css", TRUE);

  // Inicializar gtk
  gtk_init(NULL, NULL);

  // gen_login();
  // gen_formpac();
  gen_formed();
  // gen_formprov();
  // gen_formcons();
  // prueba();
  // gen_menu();

  gtk_main();
  return 0;
}
