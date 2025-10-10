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
/* Crea un nuevo proceso dplicando el proceso actual */
    int processID = fork();
/* si se devuelve un numero positivo es el proceso padre */
    if (processID > 0) {
        printf("\n proceso padre.... \n");
    }
/* si devuelve 0 estamos en el proceso hijo */
    else if (processID == 0) {
        printf("\n proceso hijo recien creado \n");
    }
/* si devuelve un valor negativo es que hubo un error */
    else {
        printf("\n llamada al sistema fork() falló\n");
    }

    printf("\n\n Imprimiendo ... \n");
    for (int i = 0; i < 5; i++)
        printf(" %d \n", i);

    printf("\n Fin \n");

    return 0;
}
