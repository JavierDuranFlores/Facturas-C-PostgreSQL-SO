#include "../../include/service/detalle_factura_service.h"


Detalle_Facturas * recolectar_datos_detalle_factura(){

    //vacia_buffer();

    /*printf("Digite su folio de Factura: ");
    char * descripcion = nextLine();*/

    printf("Digite el Id de articulo: " );
	char * id_articulo = nextLine();

    printf("Digite la cantidad: ");
	char * cantidad = nextLine();

    printf("Digite el subtotal");
	char * subtotal = nextLine();

    return detalle_facturas_constructor ("3", id_articulo, cantidad, subtotal);

}

void agregar_detalle_factura_servicio(PGconn *conn) {

    Detalle_Facturas * detalle_facturas = recolectar_datos_detalle_factura();

    agregar_todos(conn, "insertar_detalle_factura ", 4, detalle_facturas->folio, detalle_facturas->id_articulo, detalle_facturas->cantidad, detalle_facturas->subtotal);

}

void actualizar_detalle_factura_servicio(PGconn * conn, char * columna) {
    vacia_buffer();
    printf("Ingrese nueva informacion (%s): ", columna);
    char * nueva = nextLine();
    printf("Id del detalle factura: ");
    char * id = nextLine();
    actualizar_todos(conn, "actualizar ", 4, columna, nueva, id, "detalle_facturas");
}

void eliminar_detalle_factura_servicio(PGconn * conn) {
    vacia_buffer();
    printf("Id del detalle factura: ");
    char * id = nextLine();
    eliminar_todos(conn, "eliminar_detalle_factura ", 1, id);
}