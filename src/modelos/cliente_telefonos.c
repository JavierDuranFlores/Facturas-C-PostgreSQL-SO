#include "../../include/cliente_telefonos.h"

Cliente_Telefonos * cliente_telefonos_constructor (char * telefono, char * id_cliente) {

	Cliente_Telefonos * nuevo = (Cliente_Telefonos *) malloc (sizeof(Cliente_Telefonos));

	nuevo->telefono = telefono;
	nuevo->id_cliente = id_cliente;

	return nuevo;
}


