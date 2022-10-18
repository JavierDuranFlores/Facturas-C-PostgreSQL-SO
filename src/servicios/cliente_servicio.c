#include "../../include/service/cliente_service.h"

Cliente * recolectar_datos_cliente(){

    vacia_buffer();

    printf("Digite su nombre: ");
    char * nombre = nextLine();

    printf("Digite su apellido: ");
    char * apellido = nextLine();

    printf("Digite su rfc: ");
    char * rfc = nextLine();

    printf("Digite su direccion: ");
    char * direccion = nextLine();

    printf("Digite su edad: ");
    char * edad = nextLine();

    printf("Digite su pais: ");
    char * pais = nextLine();

    return cliente_constructor (nombre, apellido, rfc, direccion,  edad, pais);
}

void agregar_cliente_servicio(PGconn *conn) {

    struct Cliente * cliente = recolectar_datos_cliente();

    agregar_todos(conn, "insertar_cliente ", 6, cliente->nombre, cliente->apellido, cliente->rfc, cliente->direccion, cliente->edad, cliente->pais);

}

void actualizar_cliente_servicio(PGconn * conn, char * columna) {
    vacia_buffer();
    printf("Ingrese nueva informacion (%s): ", columna);
    char * nueva = nextLine();
    printf("Id del Cliente: ");
    char * id = nextLine();
    actualizar_todos(conn, "actualizar ", 4, columna, nueva, id, "clientes");
}

void eliminar_cliente_servicio(PGconn * conn) {
    vacia_buffer();
    printf("Id del Cliente: ");
    char * id = nextLine();
    eliminar_todos(conn, "eliminar_cliente ", 1, id);
}