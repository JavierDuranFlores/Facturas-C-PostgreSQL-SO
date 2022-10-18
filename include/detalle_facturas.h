#ifndef DETALLE_FACTURAS_H
#define DETALLE_FACTURAS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Detalle_Facturas {
	char * folio;
	char * id_articulo;
	char * cantidad;
	char * subtotal;
}Detalle_Facturas;

Detalle_Facturas * detalle_facturas_constructor(char * folio, char * id_articulo, char * cantidad, char * subtotal);

#endif
