#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fileutil.h"

int bytesDeArchivo(char *nombre){

	// Apuntador a estructura tipo "FILE", de esta se extraera informacion de un archivo.
	FILE *archivo;
	
	// Contador de bytes para el tamaño del archivo.
	int contador = 0;

	// Abrimos el archivo en modo binario de lectura ("rb").
	archivo = fopen(nombre, "r");

	// fgetc retorna el carácter siguiente apuntado por el stream de parametro.
	// El final es igual al valor constante EOF.
  	while(fgetc(archivo) != EOF){

  		contador++;
  	}

  	return contador;
}

 char **listarArchivos(char *ruta, int *nArchivos){

	// El directorio se manipulara con un puntero estructura tipo "DIR" (flujo del directorio).
  	DIR *dir;
	
	// Abrimos el directorio, si no se puede abrir "opendir" retorna NULL.
  	dir = opendir(ruta);

	// Arreglo de cadenas de caracteres usado para almacenar los nombre de los archivos.
	char **arreglo = (char **)malloc(sizeof(char *));

	// Tamano de ruta
	int tamanoRuta = sizeof(ruta) + 1;

	// Comprobamos que se pudo abrir el directorio.
  	if (dir == NULL){
	
		printf("No se puede abrir el directorio especificado.\n");
		return arreglo;
	}
	
	// Contador usado para almacenar los nombres al arreglo ordenadamente y retornar la cantidad total de archivos encontrados.
	int contador = 0;
	
	// En *entrada habra informacion sobre los archivos en el directorio (dirent son entradas al directorio).
  	struct dirent *entrada;
	
  	// Leeemos los archivos del directorio iterativamente hasta el ultimo.
  	while((entrada = readdir(dir)) != NULL){
      		
  		// Comprobamos que sea un archivo valido lo que encontramos, si es asi lo guardamos.
  		if(entrada->d_type != DT_DIR){
				
			// Redimencionamos el tamaño de memoria asiganado al apuntador "arreglo". 
  			arreglo = (char **)realloc(arreglo, (sizeof(char *) * (contador + 1)));
			// Asignamos la memoria necesaria para almacenar el nombre del archivo.
            arreglo[contador] = (char *)malloc((sizeof(entrada->d_name) * sizeof(char)) + tamanoRuta);
			// Guardamos el nombre del archivo con la ruta.
			strcpy(arreglo[contador], ruta);
			strcat(arreglo[contador], "/");
			strcat(arreglo[contador], entrada->d_name);
			contador++;		
    	}
	}	
    
    // Cerramos el directorio.
	closedir (dir);
    
	// Guardamos la cantidad de archivos encontrados.
    *nArchivos = contador;
    
    return arreglo;
}
