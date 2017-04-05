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
	
	// Numero de archivos, el tamano total de los archivos del directorio
	// y un contador para aceder al arreglo.
    int nArchivos = 0, tamanoTotal = 0, contador = 0;
    
    // Arreglo de cadena de caracteres donde se guardan los nombres de los archivos.
	char **arreglo = listarArchivos(argv[1], &nArchivos);
	
	printf("Estudiante_1: 201523548.\n");
	printf("Estudiante_2: 201533597.\n");
	printf("Total archivos: %d.\n", nArchivos);
	
	// Calcular el tamaño en bytes de cada archivo encontrado.
	while(nArchivos--){
		
		tamanoTotal += bytesDeArchivo(arreglo[contador]);
		contador++;
	}

	printf("Total bytes: %d.\n", tamanoTotal);
  	
  	return 0;
}
