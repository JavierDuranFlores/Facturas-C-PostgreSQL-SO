#ifndef ARTICULO_H
#define ARTICULO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Articulo {
	char * descripcion;
	char * cantidad;
	char * fecha_ingreso;
	char * precio;
	char * descuento;
}Articulo;

Articulo * articulo_constructor (char * descripcion, char * cantidad, char * fecha_ingreso,
  				 char * precio, char * descuento);

#endif
