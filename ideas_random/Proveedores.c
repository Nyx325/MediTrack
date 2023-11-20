#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    GESTIÓN DE INFORMACIÓN DE PROVEEDORES
    
    nombreComercial[100]; 
    nombreFactura[100];
    rfc[15];
    domicilio[100];
    numeroOficina[15];
    whatsappEmpresarial[15];
    correoElectronico[100];
    representanteComercial[100];
    permisoNarcoticos[3];
    fecha de vigencia, datos insertados por separado. 
*/

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Proveedor {
    char nombreComercial[100];
    char nombreFactura[100];
    char rfc[15];
    char domicilio[100];
    char numeroOficina[15];
    char whatsappEmpresarial[15];
    char correoElectronico[100];
    char representanteComercial[100];
    char permisoNarcoticos[3];
    struct Fecha vigencia;
};

void agregarProveedor(FILE *archivo);
void buscarProveedor(FILE *archivo, const char rfcBuscar[15]);
void eliminarProveedor(FILE *archivo, const char rfcEliminar[15]);
void modificarProveedor(FILE *archivo, const char rfcModificar[15]);

int main() {
    FILE *archivo;
    archivo=fopen("proveedores.dat", "rb+");  // Debe ser lectura y escritura

    if (archivo==NULL) {
        archivo=fopen("proveedores.dat", "wb+");  
        if (archivo==NULL) {
            printf("Error al abrir el archivo.\n");
            return 1;
        }
    }

    int opcion;
    char rfcBuscar[15];

    do {
        printf("\nOpciones:\n");
        printf("1. Agregar Proveedor\n");
        printf("2. Buscar Proveedor\n");
        printf("3. Eliminar Proveedor\n");
        printf("4. Modificar Proveedor\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProveedor(archivo);
                break;
            case 2:
                printf("Ingrese el RFC a buscar: ");
                scanf(" %14[^\n]", rfcBuscar);
                buscarProveedor(archivo, rfcBuscar);
                break;
            case 3:
                printf("Ingrese el RFC a eliminar: ");
                scanf(" %14[^\n]", rfcBuscar);
                eliminarProveedor(archivo, rfcBuscar);
                break;
            case 4:
                printf("Ingrese el RFC a modificar: ");
                scanf(" %14[^\n]", rfcBuscar);
                modificarProveedor(archivo, rfcBuscar);
                break;
            case 5:
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    fclose(archivo);
    return 0;
}


void agregarProveedor(FILE *archivo){
    struct Proveedor proveedor;

    printf("Ingresa el nombre comercial: ");
    scanf(" %99[^\n]", proveedor.nombreComercial);
    printf("Ingresa el nombre de factura: ");
    scanf(" %99[^\n]", proveedor.nombreFactura);
    printf("Ingresa el RFC: ");
    scanf(" %14[^\n]", proveedor.rfc);
    printf("Ingresa el domicilio: ");
    scanf(" %99[^\n]", proveedor.domicilio);
    printf("Ingresa el número telefónico de la oficina: ");
    scanf(" %14[^\n]", proveedor.numeroOficina);
    printf("Ingresa el WhatsApp empresarial: ");
    scanf(" %14[^\n]", proveedor.whatsappEmpresarial);
    printf("Ingresa el correo electrónico: ");
    scanf(" %99[^\n]", proveedor.correoElectronico);
    printf("Ingresa el representante comercial: ");
    scanf(" %99[^\n]", proveedor.representanteComercial);
    printf("¿Cuenta con permiso de venta de narcóticos? (si/no): ");
    scanf(" %2[^\n]", proveedor.permisoNarcoticos);
    printf("Ingresa el día de vigencia: ");
    scanf("%d", &proveedor.vigencia.dia);
    printf("Ingresa el mes de vigencia: ");
    scanf("%d", &proveedor.vigencia.mes);
    printf("Ingresa el año de vigencia: ");
    scanf("%d", &proveedor.vigencia.anio);

    // Poner el puntero al final del arch antes de escribir
    fseek(archivo, 0, SEEK_END);

    fwrite(&proveedor, sizeof(struct Proveedor), 1, archivo);
    printf("Proveedor agregado con éxito.\n");
}

void buscarProveedor(FILE *archivo, const char rfcBuscar[15]){
    struct Proveedor proveedor;

    fseek(archivo, 0, SEEK_SET);

    while (fread(&proveedor, sizeof(struct Proveedor), 1, archivo)==1){
        if (strcmp(rfcBuscar, proveedor.rfc)==0) {
            printf("Proveedor encontrado:\n");
            printf("Nombre Comercial: %s\n", proveedor.nombreComercial);
            printf("Nombre de Factura: %s\n", proveedor.nombreFactura);
            printf("RFC: %s\n", proveedor.rfc);
            printf("Domicilio: %s\n", proveedor.domicilio);
            printf("Número de Oficina: %s\n", proveedor.numeroOficina);
            printf("WhatsApp Empresarial: %s\n", proveedor.whatsappEmpresarial);
            printf("Correo Electrónico: %s\n", proveedor.correoElectronico);
            printf("Representante Comercial: %s\n", proveedor.representanteComercial);
            printf("Permiso de Venta de Narcóticos: %s\n", proveedor.permisoNarcoticos);
            printf("Vigencia: %02d/%02d/%04d\n", proveedor.vigencia.dia, proveedor.vigencia.mes, proveedor.vigencia.anio);
            return;  
        }
    }
    printf("Proveedor no encontrado.\n");
}

void eliminarProveedor(FILE *archivo, const char rfcEliminar[15]){
    struct Proveedor proveedor;
    FILE *tempFile=fopen("temp.dat", "wb+");

    if (tempFile==NULL){
        printf("Error al abrir el archivo temporal.\n");
        return;
    }

    int eliminado=0;

    fseek(archivo, 0, SEEK_SET);

    while (fread(&proveedor, sizeof(struct Proveedor), 1, archivo)==1) {
        if (strcmp(rfcEliminar, proveedor.rfc)!=0) {
            fwrite(&proveedor, sizeof(struct Proveedor), 1, tempFile);
        } else {
            eliminado=1;
        }
    }

    fclose(archivo);
    fclose(tempFile);

    remove("proveedores.dat");
    rename("temp.dat", "proveedores.dat");

    if (eliminado) {
        printf("Proveedor eliminado con éxito.\n");
    } else {
        remove("temp.dat");
        printf("Proveedor no encontrado.\n");
    }
}

void modificarProveedor(FILE *archivo, const char rfcModificar[15]) {
    struct Proveedor proveedor;
    FILE *tempFile=fopen("temp.dat", "wb+");

    if (tempFile==NULL) {
        printf("Error al abrir el archivo temporal.\n");
        return;
    }

    int modificado=0;

    fseek(archivo, 0, SEEK_SET);

    while (fread(&proveedor, sizeof(struct Proveedor), 1, archivo)==1) {
        if (strcmp(rfcModificar, proveedor.rfc)==0) {
            printf("Modifique los datos del proveedor:\n");
            printf("Ingrese el nuevo nombre comercial: ");
            scanf(" %99[^\n]", proveedor.nombreComercial);
            printf("Ingrese el nuevo nombre de factura: ");
            scanf(" %99[^\n]", proveedor.nombreFactura);
            printf("Ingrese el nuevo domicilio: ");
            scanf(" %99[^\n]", proveedor.domicilio);
            printf("Ingrese el nuevo número de oficina: ");
            scanf(" %14[^\n]", proveedor.numeroOficina);
            printf("Ingrese el nuevo WhatsApp empresarial: ");
            scanf(" %14[^\n]", proveedor.whatsappEmpresarial);
            printf("Ingrese el nuevo correo electrónico: ");
            scanf(" %99[^\n]", proveedor.correoElectronico);
            printf("Ingrese el nuevo representante comercial: ");
            scanf(" %99[^\n]", proveedor.representanteComercial);
            printf("Ingrese el nuevo permiso de venta de narcóticos (si/no): ");
            scanf(" %9[^\n]", proveedor.permisoNarcoticos);
            printf("Ingrese el nuevo día de vigencia: ");
            scanf("%d", &proveedor.vigencia.dia);
            printf("Ingrese el nuevo mes de vigencia: ");
            scanf("%d", &proveedor.vigencia.mes);
            printf("Ingrese el nuevo año de vigencia: ");
            scanf("%d", &proveedor.vigencia.anio);
            modificado=1;
        }

        fwrite(&proveedor, sizeof(struct Proveedor), 1, tempFile);
    }

    fclose(archivo);
    fclose(tempFile);

    remove("proveedores.dat");
    rename("temp.dat", "proveedores.dat");

    if (modificado) {
        printf("Proveedor modificado con éxito.\n");
    } else {
        printf("Proveedor no encontrado. No se ha realizado ninguna modificación.\n");
    }
}

