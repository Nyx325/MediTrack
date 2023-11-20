#include <gtk/gtk.h>
#include <stdio.h>

int main() {
    const gchar *text = "Hola"; // Una cadena de ejemplo en UTF-8
    gsize length = g_utf8_strlen(text, -1); // -1 para contar hasta el terminador nulo

    printf("La longitud de la cadena en caracteres UTF-8 es: %zu\n", length);

    return 0;
}
