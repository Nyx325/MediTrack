#include "login.h"
#include "consultas.h"

int main() {
  // Establecer la variable de entorno GTK_THEME con la ruta al tema descargado
  g_setenv("GTK_THEME", "../theme/gtk.css", TRUE);
  
/*
#ifdef _WIN32
  if (carpeta_existe("..\\data\\"))
    if (!carpeta_existe("..\\data\\consultas"))
      return 1;
#else
  if (carpeta_existe("../data/"))
    if (!carpeta_existe("../data/consultas"))
      return 1;
#endif
*/
  // Inicializar gtk
  gtk_init(NULL, NULL);

  gen_login();

  gtk_main();
  return 0;
}
