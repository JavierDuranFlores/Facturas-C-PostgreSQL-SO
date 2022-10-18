#include "../../include/factura.h"

Factura * factura_constructor (char * fecha_factura, char* importe_total, char * importe_letra, char * id_cliente) {

	Factura * nuevo = (Factura *) malloc (sizeof(Factura));

	nuevo->fecha_factura = fecha_factura;
	nuevo->importe_total = importe_total;
	nuevo->importe_letra = importe_letra;
	nuevo->id_cliente = id_cliente;


	printf("Agrego");

	return nuevo;

}


