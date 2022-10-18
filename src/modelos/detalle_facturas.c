#include "../../include/detalle_facturas.h"

Detalle_Facturas * detalle_facturas_constructor(char * folio, char * id_articulo, char * cantidad, char * subtotal) {

	Detalle_Facturas * nuevo = (Detalle_Facturas *) malloc (sizeof(Detalle_Facturas));

	nuevo->folio = folio;
	nuevo->id_articulo = id_articulo;
	nuevo->cantidad = cantidad;
	nuevo->subtotal = subtotal;

	return nuevo;

}
