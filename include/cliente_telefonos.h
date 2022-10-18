#ifndef CLIENTE_TELEFONOS_H
#define CLIENTE_TELEFONOS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente_Telefonos {
	char * telefono;
	char * id_cliente;    
}Cliente_Telefonos;

Cliente_Telefonos * cliente_telefonos_constructor (char * telefono, char * id_cliente);

#endif
