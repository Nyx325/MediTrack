#include <stdio.h>
#include <string.h>

/*GESTIÓN DE INFORMACIPÓN DE LOS MEDICAMENTOS.
Clave de sector salud/ID- 010.000.5275.00 -
http://www.csg.gob.mx/descargas/pdf/priorizacion/cuadro-basico/med/catalogo/2016/EDICION_2016_MEDICAMENTOS.pdf#page=191&zoom=100,72,642
marcA -
substancia o combinados
gramaje
presentaciC3n
laboratorio
unidades por caja
costo
lote
caducidad
nC:mero de unidades en inventario.*/

struct Fecha {
  int dia;
  int mes;
  int anio;
};

struct Medicamento {
  int id;
  char marca[50];
  char sustancia[50];
  float gramaje;
  char presentacion[50];
  char laboratorio[50];
  int unidadesCaja;
  float costo;
  char lote[20];
  struct Fecha fecha;
  int unidadesInventario;
};

void mostrarMedicamento(struct Medicamento med);
void agregarMedicamento(FILE *archivo);
void eliminarMedicamento(FILE *archivo, int idEliminar);
void modificarMedicamento(FILE *archivo, int idmodificar);
void buscarMedicamento(FILE *archivo, int idbuscar);

int main() {
  FILE *archivo = fopen("inventario.dat", "ab+");
  if (archivo == NULL) {
    perror("Archivo no disponible");
    return 1;
  }

  char opc;
  int idEliminar, idmodificar, idbuscar;

  do {
    printf("MEDICAMENTO:\n");
    printf("1. Agregar medicamento\n");
    printf("2. Eliminar medicamento\n");
    printf("3. Modificar información del medicamento\n");
    printf("4. Buscar medicamento\n");
    printf("5. Salir\n");
    printf("Ingrese la opción a ejecutar: ");
    scanf(" %c", &opc);

    switch (opc) {
    case '1':
      agregarMedicamento(archivo);
      break;

    case '2':
      printf("Lista de los medicamentos ingresados en MediTrack.\n");
      buscarMedicamento(archivo, 0);
      printf("Ingresa el ID del medicamento a eliminar:");
      scanf("%d", &idEliminar);
      eliminarMedicamento(archivo, idEliminar);
      break;

    case '3':
      printf("Ingresa el ID del medicamento a modificar:");
      scanf("%d", &idmodificar);
      modificarMedicamento(archivo, idmodificar);
      break;

    case '4':
      printf("Ingresa el ID del medicamento a consultar:");
      scanf("%d", &idbuscar);
      buscarMedicamento(archivo, idbuscar);
      break;

    default:
      printf("Opción no válida. Intente de nuevo.\n");
    }
  } while (opc != '5');

  fclose(archivo);

  return 0;
}

void mostrarMedicamento(struct Medicamento med) {
  printf("ID: %d\n", med.id);
  printf("Marca: %s\n", med.marca);
  printf("Sustancia: %s\n", med.sustancia);
  printf("Gramaje: %.2f\n", med.gramaje);
  printf("Presentación: %s\n", med.presentacion);
  printf("Laboratorio: %s\n", med.laboratorio);
  printf("Unidades por caja: %d\n", med.unidadesCaja);
  printf("Costo: %.2f\n", med.costo);
  printf("Lote: %s\n", med.lote);
  printf("Fecha de caducidad:\n");
  printf("Dia: %d\n", med.fecha.dia);
  printf("Mes: %d\n", med.fecha.mes);
  printf("Año: %d\n", med.fecha.anio);
  printf("Unidades en inventario: %d\n", med.unidadesInventario);
}

void agregarMedicamento(FILE *archivo) {
  struct Medicamento nuevoMedicamento;
  printf("Ingresa el ID del medicamento:");
  scanf(" %d", &nuevoMedicamento.id);

  printf("Ingresa la marca:");
  scanf(" %49[^\n]", nuevoMedicamento.marca);

  printf("Ingresa la sustancia o combinados:");
  scanf(" %49[^\n]", nuevoMedicamento.sustancia);

  printf("Ingresa el gramaje:");
  scanf("%f", &nuevoMedicamento.gramaje);

  printf("Ingresa la presentación:");
  scanf(" %49[^\n]", nuevoMedicamento.presentacion);

  printf("Ingresa el laboratorio:");
  scanf(" %49[^\n]", nuevoMedicamento.laboratorio);

  printf("Ingresa las unidades por caja:");
  scanf("%d", &nuevoMedicamento.unidadesCaja);

  printf("Ingresa el costo:");
  scanf("%f", &nuevoMedicamento.costo);

  printf("Ingresa el lote:");
  scanf(" %19[^\n]", nuevoMedicamento.lote);

  printf("Ingresa fecha de caducidad (Día):");
  scanf("%d", &nuevoMedicamento.fecha.dia);

  printf("Ingresa fecha de caducidad (Mes):");
  scanf("%d", &nuevoMedicamento.fecha.mes);

  printf("Ingresa fecha de caducidad (Año):");
  scanf("%d", &nuevoMedicamento.fecha.anio);

  printf("Ingresa el número de unidades en inventario:");
  scanf("%d", &nuevoMedicamento.unidadesInventario);

  fwrite(&nuevoMedicamento, sizeof(struct Medicamento), 1, archivo);
  printf("Medicamento agregado correctamente.\n");
}

void eliminarMedicamento(FILE *archivo, int idEliminar) {
  FILE *tempFile = fopen("temp.dat", "wb+");
  if (tempFile == NULL) {
    perror("Archivo no disponible");
    return;
  }

  struct Medicamento medicamento;
  int eliminado = 0;

  fseek(archivo, 0, SEEK_SET); // Colocarme al inicio del arch para poder llevar
                               // a cabo los procedimientos

  while (fread(&medicamento, sizeof(struct Medicamento), 1, archivo) == 1) {
    if (medicamento.id != idEliminar) {
      fwrite(&medicamento, sizeof(struct Medicamento), 1, tempFile);
    } else {
      eliminado = 1;
    }
  }
  fclose(archivo);
  fclose(tempFile);
  remove("inventario.dat");
  rename("temp.dat", "inventario.dat");

  if (eliminado) {
    printf("Medicamento eliminado correctamente.\n");
  } else {
    remove("temp.dat");
    printf("Medicamento no encontrado.\n");
  }
}

void modificarMedicamento(FILE *archivo, int idmodificar) {
  FILE *tempFile = fopen("temp.dat", "wb+");
  if (tempFile == NULL) {
    perror("Archivo no disponible");
    return;
  }

  struct Medicamento medicamento;
  int encontrado = 0;

  while (fread(&medicamento, sizeof(struct Medicamento), 1, archivo) == 1) {
    if (medicamento.id == idmodificar) {
      encontrado = 1;
      printf("Ingresa los nuevos datos del medicamento:\n");

      printf("Ingresa la marca:");
      scanf(" %49[^\n]", medicamento.marca);

      printf("Ingresa la sustancia o combinados:");
      scanf(" %49[^\n]", medicamento.sustancia);

      printf("Ingresa el gramaje:");
      scanf("%f", &medicamento.gramaje);

      printf("Ingresa la presentación:");
      scanf(" %49[^\n]", medicamento.presentacion);

      printf("Ingresa el laboratorio:");
      scanf(" %49[^\n]", medicamento.laboratorio);

      printf("Ingresa las unidades por caja:");
      scanf("%d", &medicamento.unidadesCaja);

      printf("Ingresa el costo:");
      scanf("%f", &medicamento.costo);

      printf("Ingresa el lote:");
      scanf(" %19[^\n]", medicamento.lote);

      printf("Ingresa fecha de caducidad (Día):");
      scanf("%d", &medicamento.fecha.dia);

      printf("Ingresa fecha de caducidad (Mes):");
      scanf("%d", &medicamento.fecha.mes);

      printf("Ingresa fecha de caducidad (Año):");
      scanf("%d", &medicamento.fecha.anio);

      printf("Ingresa el número de unidades en inventario:");
      scanf("%d", &medicamento.unidadesInventario);
    }
    fwrite(&medicamento, sizeof(struct Medicamento), 1, tempFile);
  }

  fclose(archivo);
  fseek(tempFile, 0, SEEK_SET);
  fclose(tempFile);

  if (!encontrado) {
    printf("Medicamento no encontrado.\n");
  } else {
    remove("inventario.dat");
    rename("temp.dat", "inventario.dat");
    printf("La informaciónrmación del medicamento ha sido modificada "
           "correctamente.\n");
  }
}

void buscarMedicamento(FILE *archivo, int idbuscar) {
  struct Medicamento medicamento;
  int encontrado = 0;

  fseek(archivo, 0, SEEK_SET);

  while (fread(&medicamento, sizeof(struct Medicamento), 1, archivo) == 1) {
    if (idbuscar == 0 || medicamento.id == idbuscar) {
      mostrarMedicamento(medicamento);
      encontrado = 1;
      if (idbuscar != 0)
        break;
    }
  }

  if (!encontrado) {
    if (idbuscar != 0) {
      printf("Medicamento no encontrado.\n");
    } else {
      printf("No hay medicamentos en el inventario.\n");
    }
  }
}
