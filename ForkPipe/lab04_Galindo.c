/* *******************************************
* Pontificia Universidad Javeriana
* Autor: Mateo Galindo
* Fecha: 09/10/2025
* Materia: Sistemas operativos
* Temas: Comunicacion entre procesos con tuberias (PIPES)
- Comunicacion entre un proceso padre e hijo a traves de una tuberia
********************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t hijo_PID;

    /* Creación de la tubería de comunicación */
    if (pipe(pipefd) == -1) {
        perror("Error al crear la tubería");
        exit(EXIT_FAILURE);
    }

    /* Creación del proceso hijo */
    hijo_PID = fork();

    if (hijo_PID == -1) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    /* SE DUPLICA EL PROCESO */
    if (hijo_PID == 0) {
        /* ====== PROCESO HIJO ====== */
        printf("\n[HIJO] Mi PID es %d, el PID de mi padre es %d\n", getpid(), getppid());

        /* Cerrar salida para lectura del pipe */
        close(pipefd[1]);

        /* Leer mensaje desde el pipe */
        char mensaje[100];
        ssize_t lecturaB = read(pipefd[0], mensaje, sizeof(mensaje));

        if (lecturaB == -1) {
            perror("Error al leer del pipe");
            exit(EXIT_FAILURE);
        }

        printf("[HIJO] Leí %zd bytes: \"%s\"\n", lecturaB, mensaje);

        close(pipefd[0]); /* Cerrar extremo de lectura */
    } 
    else {
        /* ====== PROCESO PADRE ====== */
        printf("\n[PADRE] Mi PID es %d, el PID de mi hijo es %d\n", getpid(), hijo_PID);

        /* Cerrar entrada para lectura (solo escritura) */
        close(pipefd[0]);

        char mensaje[] = "Hijo, voy a darte plata y gaseosas";
        ssize_t escrituraB = write(pipefd[1], mensaje, strlen(mensaje) + 1);

        if (escrituraB == -1) {
            perror("Error al escribir en el pipe");
            exit(EXIT_FAILURE);
        }

        printf("[PADRE] Escribí %zd bytes en el pipe.\n", escrituraB);

        close(pipefd[1]); /* Cerrar extremo de escritura */
    }

    return 0;
}
