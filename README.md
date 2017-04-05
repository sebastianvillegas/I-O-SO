# Este es un archivo *Readme.md*.

Nombres: Iván Mauricio Toro           201523548-3743
	Jhoan Sebastián Villegas     201533597-3743

fileutil.h: Contiene la declaración de las funciones usadas.   
fileutil.c: Contiene la implementación de la funciones para calcular los bytes, dar los nombres de los archivos.  
Makefile: Contiene los comandos para generar los ejecutables.
io.c: Contiene la implementación del programa sin la ayuda de la función fork().
iofork.c: Contiene la implementación del programa con la ayuda de la función fork().

Sí hay una pequeña reducción en el tiempo de ejecución pero la diferencia entre estas dos implementaciones (con fork y sin fork) no es de t/2 ya 
que es un programa que es intensivo en I/O, por lo tanto la CPU debe esperar mucho al disco duro y así se divida el trabajo, 
la espera hace que el tiempo de ejecución no se reduzca mucho.
