#ifndef DETALLE_FACTURA_H
#define DETALLE_FACTURA_H

#include "../../include/agregar.h"
#include "../../include/actualizar.h"
#include "../../include/eliminar.h"
#include "../../include/next_line.h"
#include "../../include/detalle_facturas.h"

Detalle_Facturas * recolectar_datos_detalle_factura();
void agregar_detalle_factura_servicio(PGconn *conn);
void actualizar_detalle_factura_servicio(PGconn * conn, char * columna);
void eliminar_detalle_factura_servicio(PGconn * conn);

#endif