#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int   dia;
  int   mes;
  int   anio;
} fecha;

typedef struct {
  char  nombre[50];
  char  CURP[19];
  fecha fechas;
  char  sexo;
  char  telf[11];
  char  tpSangre[4];
  fecha fechasC;
  int   estado;
} pacientes;

typedef struct {
  int   edad;
  float peso;
  float altura;
  float presArt;
  float temp;
  char  sintomas[50];
  char  alergias[50];
  char  enfermedad[50];
  char  nombreDtr[50];
  fecha fechaH;
  int   estado;
} Historico;

pacientes Paciente;
Historico historial;

int menu();
int addPaciente(char nomPac[], pacientes Paciente);
int Consultar(char nomPac[], pacientes Paciente, char CURPB[]);
void mostrarPaci(char nomPac[]);
void Modificar(char nomPac[], pacientes Paciente, char CURPB[]);
void Eliminar(pacientes Paciente, char CURPB[]);

void addHistorial(char nomPac[], char historP[], pacientes Paciente,
                  Historico historial, char CURPB[]);
void mostrarConsultas(char nomPac[], char historP[], char CURPB[]);
void OrdenarFecha(char historP[], Historico historial);
void BuscarHistorial(char nomPac[], char historP[], char CURPB[], int dia,
                     int mes, int anio);

int main() {
  char nomPac[150] = "pacientes.dat";
  char historP[150] = "historios.dat";
  char CURPB[19];
  int opc, dia, mes, anio;
  do {
    opc = menu();
    switch (opc) {
    case 1:
      if (addPaciente(nomPac, Paciente)) {
        printf("Paciente registrado exitosamente\n");
        // ordenar(nomPac);
      }
      break;
    case 2:
      printf("CURP del paciente a eliminar: ");
      scanf("%*c%[^\n]", CURPB);
      Eliminar(Paciente, CURPB);
      break;
    case 3:
      printf("CURP del paciente a modificar: ");
      scanf("%*c%[^\n]", CURPB);
      Modificar(nomPac, Paciente, CURPB);
      break;
    case 4:
      // mostrarPaci(nomPac,tam);
      printf("CURP a buscar: ");
      scanf("%*c%[^\n]", CURPB);
      Consultar(nomPac, Paciente, CURPB);
      break;
    case 5:
      mostrarPaci(nomPac);
      break;
    case 6:
      printf("CURP a buscar: ");
      scanf("%*c%[^\n]", CURPB);
      addHistorial(nomPac, historP, Paciente, historial, CURPB);
      break;
    case 7:
      printf("CURP a buscar: ");
      scanf("%*c%[^\n]", CURPB);

      break;
    case 8:
      printf("CURP a buscar: ");
      scanf("%*c%[^\n]", CURPB);

      break;
    case 9:
      printf("CURP a buscar: ");
      scanf("%*c%[^\n]", CURPB);
      printf("Ingrse la fecha de hoy en formato dd/mm/aaaa: ");
      scanf("%d/%d/%d", &dia, &mes, &anio);
      BuscarHistorial(nomPac, historP, CURPB, dia, mes, anio);
      break;
    case 10:
      printf("CURP a buscar: ");
      scanf("%*c%[^\n]", CURPB);
      mostrarConsultas(nomPac, historP, CURPB);
      break;
    case 0:
      break;
    default:
      printf("La opción ingresada no se encuentra dentro de lo solicitado\n");
      break;
    }
  } while (opc != 0);

  return 0;
}

int menu() {
  int opc;
  printf("1. Agregar paciente\n");
  printf("2. Eliminar\n");
  printf("3. Modificar\n");
  printf("4. Consultar\n");
  printf("5. Mostrar todo\n______________________________________\n");
  printf("6. Agregar consulta\n");
  printf("7. Eliminar consulta\n");
  printf("8. Modificar consulta\n");
  printf("9. Consultar consulta\n");
  printf("10. Mostrar consultas\n");
  printf("0. Salir\n");
  printf("Ingrese la opción a realizar: ");
  scanf("%d", &opc);
  return opc;
}
// Creación de la función agregar cliente
int addPaciente(char nomPac[], pacientes Paciente) {
  FILE *apPaci;

  printf("Nombre: ");
  scanf("%*c%[^\n]", Paciente.nombre);
  apPaci = fopen(nomPac, "ab");
  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return 0;
  }
  printf("CURP: ");
  scanf("%*c%[^\n]", Paciente.CURP);
  printf("Ingrese la fecha de nacimiento (DD/MM/YYYY): ");
  scanf("%*c%d/%d/%d", &Paciente.fechas.dia, &Paciente.fechas.mes,
        &Paciente.fechas.anio);
  printf("Sexo: ");
  scanf("%*c%c", &Paciente.sexo);
  printf("Número de telefono: ");
  scanf("%*c%[^\n]", Paciente.telf);
  printf("Tipo de sangre: ");
  scanf("%*c%[^\n]", Paciente.tpSangre);
  printf("Fecha de la primera consulta (DD/MM/YYYY): ");
  scanf("%*c%d/%d/%d", &Paciente.fechasC.dia, &Paciente.fechasC.mes,
        &Paciente.fechasC.anio);

  Paciente.estado = 1;

  fwrite(&Paciente, sizeof(pacientes), 1, apPaci);
  fclose(apPaci);
  return 1;
}

// Función mostrar pacientes
// void mostrarPaci(char nomPac[],pacientes Paciente){
void mostrarPaci(char nomPac[]) {
  FILE *apPaci;
  pacientes Paciente;
  apPaci = fopen(nomPac, "a+b");
  if (apPaci == NULL) {
    printf("Archivo danaño\n");
    return;
  }
  // fseek(apPaci,0,SEEK_SET);

  fread(&Paciente, sizeof(pacientes), 1, apPaci);

  while (!feof(apPaci)) {
    if (Paciente.estado) {
      //(&Paciente,sizeof(pacientes),1,apPaci);
      // fread(&Paciente.estado,sizeof(int),1,apPaci);
      // if(Paciente.estado==1){
      Paciente.nombre[29] = '\0';
      Paciente.CURP[18] = '\0';
      printf("Nombre: %s\nCURP: %s\nFecha: %d/%d/%d\nSexo: %c\nTelefono: "
             "%s\nTipo de sangre: %s\nFecha de consulta: %d/%d/%d\n",
             Paciente.nombre, Paciente.CURP, Paciente.fechas.dia,
             Paciente.fechas.mes, Paciente.fechas.anio, Paciente.sexo,
             Paciente.telf, Paciente.tpSangre, Paciente.fechasC.dia,
             Paciente.fechasC.mes, Paciente.fechasC.anio);

      // fread(Paciente.nombre,sizeof(nombre),1,apPaci);
    }
    // fread(&Paciente.estado,1,1,apPaci);
    fread(&Paciente, sizeof(pacientes), 1, apPaci);
  }
  fclose(apPaci);
}
// Funcion eliminar paciente
void Eliminar(pacientes Paciente, char CURPB[]) {
  FILE *apPaci = fopen("pacientes.dat", "r+b");

  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return;
  }
  fseek(apPaci, 0, SEEK_SET);
  fread(&Paciente, sizeof(pacientes), 1, apPaci);
  while (!feof(apPaci)) {

    if (strcmp(Paciente.CURP, CURPB) == 0) {
      fseek(apPaci, -sizeof(pacientes), 1);
      Paciente.estado = 0;
      fwrite(&Paciente, sizeof(pacientes), 1, apPaci);
      fclose(apPaci);
      return;
    }
    fread(&Paciente, sizeof(pacientes), 1, apPaci);
  }
  fclose(apPaci);
  printf("Paciente eliminado\n");
}
// Funcion modificar paciente
void Modificar(char nomPac[], pacientes Paciente, char CURPB[]) {
  FILE *apPaci;
  apPaci = fopen(nomPac, "r+b");
  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return;
  }
  fseek(apPaci, 0, SEEK_SET);

  while (fread(&Paciente, sizeof(pacientes), 1, apPaci)) {
    if (strcmp(Paciente.CURP, CURPB) == 0) {
      printf("Ingrese los nuevos datos\n");
      printf("Nombre: ");
      scanf("%*c%[^\n]", Paciente.nombre);
      printf("CURP: ");
      scanf("%*c%[^\n]", Paciente.CURP);
      printf("Ingrese la fecha de nacimiento (DD/MM/YYYY): ");
      scanf("%*c%d/%d/%d", &Paciente.fechas.dia, &Paciente.fechas.mes,
            &Paciente.fechas.anio);
      printf("Sexo: ");
      scanf("%*c%s", &Paciente.sexo);
      printf("Número de telefono: ");
      scanf("%*c%[^\n]", Paciente.telf);
      printf("Tipo de sangre: ");
      scanf("%*c%[^\n]", Paciente.tpSangre);
      printf("Fecha de la primera consulta (DD/MM/YYYY): ");
      scanf("%*c%d/%d/%d", &Paciente.fechasC.dia, &Paciente.fechasC.mes,
            &Paciente.fechasC.anio);
    }
  }

  apPaci = fopen(nomPac, "r+b");
  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return;
  }

  fseek(apPaci, 0, SEEK_SET);
  fwrite(&Paciente, sizeof(pacientes), 1, apPaci);
  fclose(apPaci);
  printf("Datos actualizados\n");
}

// Funcion consultar paciente
int Consultar(char nomPac[], pacientes Paciente, char CURPB[]) {
  FILE *apPaci;

  apPaci = fopen(nomPac, "rb");
  if (apPaci == NULL) {
    printf("Archivo danaño\n");
    return 0;
  }
  fseek(apPaci, 0, SEEK_SET);
  while (fread(&Paciente, sizeof(pacientes), 1, apPaci) == 1) {
    if (strcmp(Paciente.CURP, CURPB) == 0) {
      printf("Nombre: %s\nCURP: %s\nFecha: %d/%d/%d\nSexo: %c\nTelefono: "
             "%s\nTipo de sangre: %s\nFecha de consulta: %d/%d/%d\n",
             Paciente.nombre, Paciente.CURP, Paciente.fechas.dia,
             Paciente.fechas.mes, Paciente.fechas.anio, Paciente.sexo,
             Paciente.telf, Paciente.tpSangre, Paciente.fechasC.dia,
             Paciente.fechasC.mes, Paciente.fechasC.anio);

    } else {
      printf("Paciente no encontrado\n");
    }
  }
  fclose(apPaci);
}

void addHistorial(char nomPac[], char historP[], pacientes Paciente,
                  Historico historial, char CURPB[]) {
  FILE *apPaci;
  FILE *apHistorial;
  int edad, dia, mes, anio, estado;
  float altura, peso, presArt, temp;
  char sintomas[50], alergias[50], enfermedad[50], nombreDtr[50];

  apPaci = fopen(nomPac, "rb");
  if (apPaci == NULL) {
    printf("Archivo danaño\n");
  }
  fseek(apPaci, 0, SEEK_SET);
  while (fread(&Paciente, sizeof(pacientes), 1, apPaci) == 1) {
    if (strcmp(Paciente.CURP, CURPB) == 0) {
      printf("Nombre: %s\nCURP: %s\nFecha: %d/%d/%d\nSexo: %c\nTelefono: "
             "%s\nTipo de sangre: %s\nFecha de consulta: %d/%d/%d\n",
             Paciente.nombre, Paciente.CURP, Paciente.fechas.dia,
             Paciente.fechas.mes, Paciente.fechas.anio, Paciente.sexo,
             Paciente.telf, Paciente.tpSangre, Paciente.fechasC.dia,
             Paciente.fechasC.mes, Paciente.fechasC.anio);

    } else {
      printf("Paciente no encontrado\n");
    }
  }
  fclose(apPaci);

  printf("Edad: ");
  scanf("%d", &historial.edad);
  apHistorial = fopen(historP, "ab");
  if (apHistorial == NULL) {
    printf("Archivo dañado\n");
  }
  printf("Peso: ");
  scanf("%f", &historial.peso);
  printf("Altura: ");
  scanf("%f", &historial.altura);
  printf("presion: ");
  scanf("%f", &historial.presArt);
  printf("temperatura: ");
  scanf("%f", &historial.temp);
  printf("Sintomas: ");
  scanf("%*c%[^\n]", historial.sintomas);
  printf("Alergias: ");
  scanf("%*c%[^\n]", historial.alergias);
  printf("Enfermedades cronicas: ");
  scanf("%*c%[^\n]", historial.enfermedad);
  printf("Nombre del doctor: ");
  scanf("%*c%[^\n]", historial.nombreDtr);
  printf("Fecha de consulta (DD/MM/YYYY): ");
  scanf("%*c%d/%d/%d", &historial.fechaH.dia, &historial.fechaH.mes,
        &historial.fechaH.anio);

  historial.estado = 1;

  fwrite(&historial, sizeof(Historico), 1, apPaci);
  fclose(apHistorial);
}

void mostrarConsultas(char nomPac[], char historP[], char CURPB[]) {
  FILE *apPaci;
  pacientes Paciente;
  FILE *apHistorial;
  apPaci = fopen(nomPac, "rb");
  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return;
  }
  fseek(apPaci, 0, SEEK_SET);
  while (fread(&Paciente, sizeof(pacientes), 1, apPaci) == 1) {
    if (strcmp(Paciente.CURP, CURPB) != 0) {
      printf("Paciente no encontrado\n");
    }
  }
  fclose(apPaci);
  Historico historial;
  apHistorial = fopen(historP, "a+b");
  if (apHistorial == NULL) {
    printf("Archivo dañado\n");
    return;
  }
  fread(&historial, sizeof(Historico), 1, apHistorial);
  while (fread(&historial, sizeof(Historico), 1, apHistorial) == 1) {
    if (historial.estado == 1) {
      printf(
          "\nEdad: %d\nPeso: %.2f\nAltura: %.2f\nPresión: %.2f\nTemperatura: "
          "%.2f\nSíntomas: %s\nAlergias: %s\nEnfermedades cronicas: %s\nNombre "
          "del doctor: %s\nFecha de consulta: %d/%d/%d\n",
          historial.edad, historial.peso, historial.altura, historial.presArt,
          historial.temp, historial.sintomas, historial.alergias,
          historial.enfermedad, historial.nombreDtr, historial.fechaH.dia,
          historial.fechaH.mes, historial.fechaH.anio);
    }
    fread(&historial, sizeof(Historico), 1, apHistorial);
  }
  fclose(apHistorial);
}

void BuscarHistorial(char nomPac[], char historP[], char CURPB[], int dia,
                     int mes, int anio) {
  FILE *apPaci;
  pacientes Paciente;
  apPaci = fopen(nomPac, "rb");
  if (apPaci == NULL) {
    printf("Archivo dañado\n");
    return;
  }
  fseek(apPaci, 0, SEEK_SET);
  while (fread(&Paciente, sizeof(pacientes), 1, apPaci) == 1) {
    if (strcmp(Paciente.CURP, CURPB) != 0) {
      printf("Paciente no encontrado\n");
    }
    fclose(apPaci);
  }

  FILE *apHistorial;
  Historico historial;
  apHistorial = fopen(historP, "ab");
  if (apHistorial == NULL) {
    printf("Archivo danaño\n");
    return;
  }

  fseek(apHistorial, 0, SEEK_SET);
  while (fread(&historial, sizeof(Historico), 1, apHistorial) == 1) {
    if (historial.fechaH.dia == dia && historial.fechaH.mes == mes &&
        historial.fechaH.anio == anio) {
  printf(""\nEdad: %d\nPeso: %.2f\nAltura: %.2f\nPresión: %.2f\nTemperatura: %.2f\nSíntomas: %s\nAlergias: %s\nEnfermedades cronicas: %s\nNombre del doctor: %s\nFecha de consulta: %d/%d/%d\n",historial.edad,historial.peso,historial.altura,historial.presArt,historial.temp,historial.sintomas,historial.alergias,historial.enfermedad,historial.nombreDtr,historial.fechaH.dia,historial.fechaH.mes,historial.fechaH.anio);
    } else {
  printf("Consulta no encontrada\n");
    }

    fclose(apHistorial);
