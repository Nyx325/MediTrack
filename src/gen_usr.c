#include <stdio.h>

typedef unsigned char Opc;

typedef struct {
  Opc tipo;
  char nombreUsr[31];
  char contrasenia[31];
} Usuario;

int main() {
  Usuario new;

  printf("Ingresa el usuario (max 30 chars): ");
  scanf("%30[^\n]%*c", new.nombreUsr);
  printf("Ingresa la contraseña (max 30 chars): ");
  scanf("%30[^\n]%*c", new.contrasenia);
  do {
    printf("Ingresa el tipo: ");
    scanf("%hhu", &new.tipo);
  } while (new.tipo > 2 && new.tipo < 0);

  printf("Usuario: %s\nContraseña: %s\nTipo: %d", new.nombreUsr, new.contrasenia, new.tipo);

  FILE *arch = fopen("../data/usr", "ab");
  if (arch == NULL) {
    printf("Archivo dañado\n");
    return 1;
  }

  fwrite(&new, sizeof(Usuario), 1, arch);
  fclose(arch);
}
