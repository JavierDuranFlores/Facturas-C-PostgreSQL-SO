#ifndef FACTURA_SERVICE_H
#define FACTURA_SERVICE_H

#include "../../include/agregar.h"
#include "../../include/actualizar.h"
#include "../../include/eliminar.h"
#include "../../include/factura.h"
#include "../../include/next_line.h"
//#include "../../include/lista/lista_articulo.h"
#include "../../include/concat_punteros.h"
#include <libpq-fe.h>


Factura * recolectar_datos_factura();
void agregar_factura_servicio(PGconn *conn);
void actualizar_factura_servicio(PGconn * conn, char * columna);
void eliminar_factura_servicio(PGconn * conn);
void facturar_servicio(PGconn * conn);
ExecStatusType agregar_detalle_factura(PGconn * conn, char * name_func_postgres, int cantidad, ...);

#endif