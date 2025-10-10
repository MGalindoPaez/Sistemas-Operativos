/* *************************************
 * Pontificia Universidad Javeriana
 * Autor: Mateo Galindo
 * Fecha: 09/10/2025
 * Materia: Sistemas operativos
 * Temas: Procesos Fork
 - Padre e Hijo realizan tareas diferentes
 **************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {

    int processID = fork();

    if (processID > 0) {
        printf("\n proceso padre.... \n");
    }
    else if (processID == 0) {
        printf("\n proceso hijo recien creado \n");
    }
    else {
        printf("\n llamada al sistema fork() falló\n");
    }

    printf("\n\n Imprimiendo ... \n");
    for (int i = 0; i < 5; i++)
        printf(" %d \n", i);

    printf("\n Fin \n");

    return 0;
}
