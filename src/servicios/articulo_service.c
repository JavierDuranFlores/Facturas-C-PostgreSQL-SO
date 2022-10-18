#include "../../include/service/articulo_service.h"

Articulo * recolectar_datos_articulo(){

    vacia_buffer();

    printf("Digite su descripcion: ");
    char * descripcion = nextLine();

    printf("Digite la cantidad del producto: " );
	char * cantidad = nextLine();

    printf("Digite su fecha de ingreso: ");
	char * fecha_ingreso = nextLine();

    printf("Digite el precio del articulo");
	char * precio = nextLine();

    printf("Digite el descuento del articulo: ");
	char * descuento = nextLine();

    return articulo_constructor (descripcion, cantidad, fecha_ingreso,  precio, descuento);

}

void agregar_articulo_servicio(PGconn *conn) {

    Articulo * articulo = recolectar_datos_articulo();

    agregar_todos(conn, "insertar_articulos ", 5, articulo->descripcion, articulo->cantidad, articulo->fecha_ingreso, articulo->precio, articulo->descuento);

}

void actualizar_articulo_servicio(PGconn * conn, char * columna) {
    vacia_buffer();
    printf("Ingrese nueva informacion (%s): ", columna);
    char * nueva = nextLine();
    printf("Id del Articulo: ");
    char * id = nextLine();
    actualizar_todos(conn, "actualizar ", 4, columna, nueva, id, "articulos");
}

void eliminar_articulo_servicio(PGconn * conn) {
    vacia_buffer();
    printf("Id del Articulo: ");
    char * id = nextLine();
    eliminar_todos(conn, "eliminar_articulo ", 1, id);
}