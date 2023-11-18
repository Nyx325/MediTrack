#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Definición de un tipo de función de callback genérico
typedef void* (*ThreadFunction)(void*);

// Función genérica para crear un hilo y ejecutar una función con argumentos
pthread_t crear_hilo(ThreadFunction funcion, void* argumentos) {
    pthread_t hilo;
    pthread_create(&hilo, NULL, funcion, argumentos);
    return hilo;
}

// Ejemplo de una función que suma dos enteros
void* suma(void* arg) {
    int* args = (int*)arg;
    int resultado = args[0] + args[1];
    printf("Resultado de la suma: %d\n", resultado);
    return NULL;
}

// Ejemplo de una función que imprime una cadena
void* imprimir(void* arg) {
    char* cadena = (char*)arg;
    printf("Mensaje: %s\n", cadena);
    return NULL;
}

int main() {
    int suma_args[2] = {10, 20};
    char mensaje[] = "Hola, mundo";

    // Crear un hilo para ejecutar la función de suma
    pthread_t hilo_suma = crear_hilo(suma, suma_args);

    // Crear un hilo para ejecutar la función de imprimir
    pthread_t hilo_imprimir = crear_hilo(imprimir, mensaje);

    // Esperar a que ambos hilos terminen
    pthread_join(hilo_suma, NULL);
    pthread_join(hilo_imprimir, NULL);

    printf("El programa principal ha terminado.\n");

    return 0;
}
