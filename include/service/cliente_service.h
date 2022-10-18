#ifndef CLIENTE_SERVICE_H
#define CLIENTE_SERVICE_H

#include "../../include/agregar.h"
#include "../../include/actualizar.h"
#include "../../include/cliente.h"
#include "../../include/cliente_telefonos.h"
#include "../../include/next_line.h"
#include "../../include/eliminar.h"

Cliente * recolectar_datos_cliente();
void agregar_cliente_servicio(PGconn *conn);
void actualizar_cliente_servicio(PGconn * conn, char * columna);
void eliminar_cliente_servicio(PGconn * conn);


#endif
