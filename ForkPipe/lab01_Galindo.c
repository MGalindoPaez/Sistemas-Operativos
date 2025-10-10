/**************************************************
 * Pontificia Universidad Javeriana
 * Autor: Mateo Galindo	
 * Fecha: 09/10/2025
 * Materia: Sistemas operativos
 * Tema: Creacion de procesos fork
 * -identificacion del proceso padre e hijo
 * *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	/*Se invoca la creacion del proceso en un INT para*/
	int procesoID = fork();

	if(procesoID>0){
	/*proceso padre*/
		printf("fork() devuelve el valor -ve. Este es el proceso padre con ID: %d \n",getpid());
	}
	else if(procesoID==0){
	/*proceso hijo*/
		printf("fork devuelve un valor 0. Este es un proceso hijo recien creado con ID: %d \n", getpid());
		printf("el proceso padre de este proceso hijo tiene el ID: %d\n", getppid());
	}
	else {
	/*Error al crear el proceso*/
		printf("fork devuelve un valor -ve, por lo que la llamada al sistema fork fallo\n");
	}

	printf("\n\nEsta en una unica impresion. Si la llamada l sistema fork() ha tenido exito \n");
	printf("tanto el proceso padre como el proceso hijo se ejecutan simultaneamente, \n");
	printf("y esta impresion aparecera dos veces \n");

	return 0;
}


