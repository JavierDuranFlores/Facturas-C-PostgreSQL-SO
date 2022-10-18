#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Cliente {
   char * nombre;
   char * apellido;
   char * rfc;
   char * direccion;
   char * edad;
   char * pais;
}Cliente;

Cliente * cliente_constructor (char * nombre, char * apellido, char * rfc,
		char * direccion, char * edad, char * pais);

#endif
