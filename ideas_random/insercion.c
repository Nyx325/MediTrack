#include <stdio.h>

void insercionOrdenArchivo(const char *nombreArchivo, int tamRegistro) {
  FILE *archivo = fopen(nombreArchivo, "rb+");

  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  fseek(archivo, 0, SEEK_END);
  long tamArchivo = ftell(archivo);
  rewind(archivo);

  int totalRegistros = tamArchivo / tamRegistro;

  for (int i = 1; i < totalRegistros; i++) {
    fseek(archivo, i * tamRegistro, SEEK_SET);

    int clave, j;
    fread(&clave, sizeof(int), 1, archivo);

    j = i - 1;
    while (j >= 0) {
      int actual;
      fseek(archivo, j * tamRegistro, SEEK_SET);
      fread(&actual, sizeof(int), 1, archivo);

      if (actual <= clave) {
        break;
      }

      fseek(archivo, (j + 1) * tamRegistro, SEEK_SET);
      fwrite(&actual, sizeof(int), 1, archivo);

      j--;
    }

    fseek(archivo, (j + 1) * tamRegistro, SEEK_SET);
    fwrite(&clave, sizeof(int), 1, archivo);
  }

  fclose(archivo);
}
