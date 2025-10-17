/* ##########################
 * Pontificia Universidad Javerina
 * Autor: Mateo Galindo
 * Materia: Sistemas operativos
 * Tema: Implementacion de productor consumudor a partir de pipe named 
 * Descrpicion:
 * -Archivo liente que permite enviar mensajes a un servidor a traves de una FIFO.
 ####################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/fifo_twoway"

#define FIFO_FILE "/tmp/fifo_twoway"  
// Define el nombre y ruta del archivo FIFO (tuberia con nombre) que se usaras para la comunicacion entre procesos.

int main() {
    int fd;                // Descriptor del archivo FIFO.
    int end_process;       // Variable para verificar si el usuario quiere terminar ("end").
    int read_bytes;        // Almacena la cantidad de bytes leidos del FIFO.
    char readbuf[80];      // Buffer para almacenar el mensaje leido o escrito.
    char end_str[5];       // Cadena que contiene la palabra "end" para comparar y terminar.
    
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter 'end'\n");
    // Mensaje inicial para el usuario: puede enviar mensajes infinitamente hasta escribir "end".

    // Abrir el FIFO para lectura y escritura
    fd = open(FIFO_FILE, O_RDWR);
    // Abre el archivo FIFO en modo lectura/escritura.
    // O_RDWR permite tanto leer como escribir en el mismo descriptor.

    if (fd == -1) {
        perror("Error opening FIFO");
        exit(1);
        // Si no se puede abrir el FIFO, muestra un error y termina el programa.
    }

    strcpy(end_str, "end");
    // Copia la cadena "end" en la variable end_str para comparaciones futuras.

    // --- Bucle principal: el cliente envía mensajes hasta escribir "end" ---
    while (1) {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        // Lee una linea de texto desde la entrada estandar (teclado).

        // Elimina el salto de linea final que agrega fgets
        int stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';

        // Compara si el usuario escribio "end"
        end_process = strcmp(readbuf, end_str);

        // Si el usuario NO escribio "end"
        if (end_process != 0) {
            // Envía el mensaje al servidor a traves del FIFO
            write(fd, readbuf, strlen(readbuf) + 1);  // Se incluye el terminador nulo '\0'
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n",
                   readbuf, (int)strlen(readbuf));

            // Espera una respuesta del servidor (bloqueante)
            read_bytes = read(fd, readbuf, sizeof(readbuf));
            if (read_bytes > 0) {
                readbuf[read_bytes] = '\0';  // Asegura que el buffer termine con '\0'
                printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n",
                       readbuf, (int)strlen(readbuf));
            }

        } else {
            // Si el usuario escribio "end" --> se envía al servidor para finalizar
            write(fd, readbuf, strlen(readbuf) + 1);
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n",
                   readbuf, (int)strlen(readbuf));
            break;  // Sale del bucle y termina el programa
        }
    }

    return 0;
}

