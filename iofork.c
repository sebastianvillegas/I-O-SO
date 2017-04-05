#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fileutil.h"
 
int main(int argc, char **argv){
	
	// Comprobamos que el usuario ingreso una ruta.
  	if(argc != 2){
  		
    	printf("Has olvidado introducir la ruta del directorio.\n");
    	return 1;
    }
	
	// Numero de archivos y el tamano total de los archivos del directorio,
	// un contador para aceder al arreglo y la posicion de la mitad del arreglo.
    int nArchivos = 0, tamanoTotal = 0, contador = 0, mitad = 0;
    
    // Arreglo de cadena de caracteres donde se guardan los nombres de los archivos.
	char **arreglo = listarArchivos(argv[1], &nArchivos);

	printf("Estudiante_1: 201523548.\n");
	printf("Estudiante_2: 201533597.\n");
	printf("Total archivos: %d.\n", nArchivos);

	// Asignamos a la variable el valor de la mitad del arreglo.
	mitad = ((nArchivos / 2) + 1);
	
	// Arreglo para el pipeline y una variable para almacenar el pid de los procesos.
	int canal[2];
	int pid = 0;

	pipe(canal);
	
	// Creacion de proceso hijo.
	if((pid = fork())){
		
		// Total de bytes contados por el proceso hijo.
		int tamanoTotalH = 0;
		close(canal[1]);
		
		// Calcular el tamaño en bytes de cada archivo encontrado.
		while(mitad--){
			
			tamanoTotal += bytesDeArchivo(arreglo[contador]);
			contador++;
		}
		
		// Esperarndo el total de bytes contados por el hijo.
		read(canal[0], &tamanoTotalH, sizeof(tamanoTotalH));
		
		printf("Total bytes: %d.\n", (tamanoTotal + tamanoTotalH));
	}
	
	else {
		
		// Reasigna los valores para el proceso hijo.
		close(canal[0]);
		contador = mitad;
		mitad = (nArchivos - mitad);
		
		// Calcular el tamaño en bytes de cada archivo encontrado.
		while(mitad--){

			tamanoTotal += bytesDeArchivo(arreglo[contador]);
			contador++;
		}
		
		// Envia el total de bytes contados al proceso padre.
		write(canal[1], &tamanoTotal, sizeof(tamanoTotal));	
	}
  	
  	return 0;
}
