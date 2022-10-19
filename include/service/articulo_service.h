#ifndef ARTICULO_SERVICE_H
#define ARTICULO_SERVICE_H

/*#include "../../include/agregar.h"
#include "../../include/articulo.h"
#include "../../include/next_line.h"
#include "../../include/actualizar.h"
#include "../../include/eliminar.h"*/
#include "../../include/leer.h"
#include "../../include/next_line.h"
#include <libpq-fe.h>

/*Articulo * recolectar_datos_articulo();
void agregar_articulo_servicio(PGconn *conn);
void actualizar_articulo_servicio(PGconn * conn, char * columna);
void eliminar_articulo_servicio(PGconn * conn);*/

PGconn * conexion_db();
void comprobar_estadodb();

#endif