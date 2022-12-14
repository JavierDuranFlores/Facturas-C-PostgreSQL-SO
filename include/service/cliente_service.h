#ifndef CLIENTE_SERVICE_H
#define CLIENTE_SERVICE_H

//#include "../../include/agregar.h"
//#include "../../include/actualizar.h"
#include "../../include/leer.h"
#include "../../include/cliente.h"
#include "../../include/cliente_telefonos.h"
#include "../../include/next_line.h"
#include <libpq-fe.h>
//#include "../../include/eliminar.h"

Cliente * recolectar_datos_cliente();
void menu_agregar();
void menu_actualizar();
void menu_leer();
void menu_eliminar();
void menu_actualizar_cliente();
void menu_actualizar_articulo();
void menu_actualizar_factura();
//void agregar_cliente_servicio(PGconn *conn);
//void actualizar_cliente_servicio(PGconn * conn, char * columna);
//void eliminar_cliente_servicio(PGconn * conn);

PGconn * conexion_db();
void comprobar_estadodb();
void do_exit_(PGconn *conn, PGresult * res);

#endif
