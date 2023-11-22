#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Opc;

typedef struct {
  Opc tipo;
  char usuario[31];
  char contrasenia[31];
} Usuario;

int main() {
  Usuario new;

  printf("Usuario: ");
  scanf("%30[^\n]%*c", new.usuario);
  printf("Contraseña: ");
  scanf("%30[^\n]%*c", new.contrasenia);
  do {
    printf("Tipo: ");
    scanf("%hhu%*c", &new.tipo);
  } while (new.tipo < 0 && new.tipo > 2);

  FILE *apArch = fopen("../data/usr", "ab");
  printf("%s %s %d", new.usuario, new.contrasenia, new.tipo);
  fwrite(&new, sizeof(Usuario), 1, apArch);
  fclose(apArch);
}
