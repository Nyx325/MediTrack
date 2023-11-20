#include <gtk/gtk.h>

int main() {
  char *cadena = "Hola"; // Una cadena C estándar
  gchar *gcadena = g_strdup(cadena);

  g_print("%s\n", gcadena);

  gchar *gcadena2 = "Adios";
}
