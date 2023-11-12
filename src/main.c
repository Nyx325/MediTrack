#include "form_consul.h"
#include "form_med.h"
#include "form_pac.h"
#include "form_prov.h"
#include "general.h"
#include "login.h"

int main() {
  // Establecer la variable de entorno GTK_THEME con la ruta al tema descargado
  g_setenv("GTK_THEME", "../theme/gtk.css", TRUE);

  // Inicializar gtk
  gtk_init(NULL, NULL);

  // gen_login();
  // gen_formpac();
  // TODO gen_formed();
  // gen_formprov();
  // gen_formcons();

  gtk_main();
  return 0;
}
