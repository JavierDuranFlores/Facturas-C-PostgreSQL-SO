#include "../../include/articulo.h"

Articulo * articulo_constructor (char * descripcion, char * cantidad, char * fecha_ingreso,
				char * precio, char * descuento) {

	struct Articulo * articulo = (Articulo *) malloc (sizeof(Articulo));

	articulo->descripcion = descripcion;
	articulo->cantidad = cantidad;
	articulo->fecha_ingreso = fecha_ingreso;
	articulo->precio = precio;
	articulo->descuento = descuento;

	printf("Agrego");

	return articulo;
}
