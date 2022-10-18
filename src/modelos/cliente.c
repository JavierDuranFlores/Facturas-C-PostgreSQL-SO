#include "../../include/cliente.h"

Cliente * cliente_constructor (char * nombre, char * apellido, char * rfc, 
			     char * direccion, char * edad, char * pais) {
	struct Cliente * nuevo = (Cliente *) malloc (sizeof(Cliente));
	nuevo->nombre = nombre;
	nuevo->apellido = apellido;
	nuevo->rfc = rfc;
	nuevo->direccion = direccion;
	nuevo->pais = pais;
	nuevo->edad = edad;

	return nuevo;
}
