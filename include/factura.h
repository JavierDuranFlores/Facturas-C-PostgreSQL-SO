#ifndef FACTURA_H
#define FACTURA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Factura {
	char * fecha_factura;
	char * importe_total;
	char * importe_letra;
	char * id_cliente;
}Factura;

Factura * factura_constructor(char * fecha_factura, char* importe_total, char * importe_letra, char * id_cliente);

#endif
