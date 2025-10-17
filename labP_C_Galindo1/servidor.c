#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>      // Para usar errno y EEXIST
#include <sys/stat.h>   // Para usar mkfifo

#define FIFO_FILE "/tmp/fifo_twoway"
// Se define el nombre del archivo FIFO que se usara para comunicarse

void reverse_string(char *);  
// Se declara una funcion que invierte el texto recibido

int main() {
    int fd;               // Descriptor del archivo FIFO
    char readbuf[80];     // Buffer donde se guarda el mensaje recibido
    char end[10];         // Guarda la palabra "end"
    int to_end;           // Indica si se recibio el mensaje "end"
    int read_bytes;       // Cantidad de bytes leidos del FIFO

    // Crea el archivo FIFO si no existe
    mkfifo(FIFO_FILE, S_IFIFO | 0640);

    strcpy(end, "end");
    // Copia la palabra "end" en la variable para compararla luego

    // Abre el FIFO solo para lectura
    fd = open(FIFO_FILE, O_RDONLY);

    // Bucle que se ejecuta hasta que el cliente envie "end"
    while (1) {
        // Lee los datos que llegan por el FIFO
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';  // Asegura que el texto termine correctamente

        printf("FIFOSERVER: Received string: \"%s\" and Length is %d\n", 
               readbuf, (int)strlen(readbuf));

        // Compara si el mensaje recibido es "end"
        to_end = strcmp(readbuf, end);

        if (to_end == 0) {
            // Si el mensaje es "end", se cierra el FIFO y se termina
            close(fd);
            break;
        }

        // Invierte el texto recibido usando la funcion reverse_string
        reverse_string(readbuf);

        // Muestra el texto invertido antes de enviarlo
        printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n",
               readbuf, (int)strlen(readbuf));

        // Envia el mensaje invertido de vuelta al cliente
        write(fd, readbuf, strlen(readbuf));

        // Espera un poco antes de leer el siguiente mensaje
        // Esto evita que el mismo proceso lea el mensaje que envio
        sleep(2);
    }

    return 0;
}

// Funcion que invierte una cadena de texto
void reverse_string(char *str) {
    int last, limit, first;
    char temp;

    last = strlen(str) - 1; // Ultima posicion de la cadena
    limit = last / 2;       // Mitad de la cadena
    first = 0;              // Primera posicion

    // Intercambia caracteres de principio a fin
    while (first < last) {
        temp = str[first];
        str[first] = str[last];
        str[last] = temp;

        first++;
        last--;
    }
    return;
}

