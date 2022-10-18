#include "../../include/service/factura_service.h"

Factura * recolectar_datos_factura(){

    vacia_buffer();

    printf("Digite su fecha factura: ");
    char * fech_factura = nextLine();

    printf("Digite su importe total: ");
    char * importe_total = nextLine();

    printf("Digite su importe letra: ");
    char * importe_letra = nextLine();

    printf("Digite su id cliente: ");
    char * id_cliente = nextLine();

    return factura_constructor (fech_factura, importe_total, importe_letra, id_cliente);
}

void agregar_factura_servicio(PGconn *conn) {

    struct Factura * factura = recolectar_datos_factura();

    agregar_todos(conn, "insertar_factura ", 4, factura->fecha_factura, factura->importe_total, factura->importe_letra, factura->id_cliente);

}

void actualizar_factura_servicio(PGconn * conn, char * columna) {
    vacia_buffer();
    printf("Ingrese nueva informacion (%s): ", columna);
    char * nueva = nextLine();
    printf("Id del Factura: ");
    char * id = nextLine();
    actualizar_todos(conn, "actualizar ", 4, columna, nueva, id, "facturas");
}

void eliminar_factura_servicio(PGconn * conn) {
    vacia_buffer();
    printf("Id de la factura: ");
    char * id = nextLine();
    eliminar_todos(conn, "eliminar_factura ", 1, id);
}

void facturar_servicio(PGconn * conn) {

    vacia_buffer();

    char * articulo = "";
    char * cantidad = "";

    printf("Id cliente: ");
    char * id_cliente = nextLine();

    PGresult * res = PQexec(conn, "BEGIN");

    PQclear(res);

    agregar_todos(conn, "insertar_facturas_id_cliente", 1, id_cliente);

    res = PQexec(conn, "SELECT folio FROM facturas ORDER BY folio DESC LIMIT 1;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        res = PQexec(conn, "ROLLBACK");
    }

    char * folio = PQgetvalue(res, 0, 0);

    char respuesta;
    do {
        printf("Nombre del Articulo: ");
        articulo = nextLine();

        printf("Cantidad del Articulo: ");
        cantidad = nextLine();

        if (agregar_detalle_factura(conn, "insertar_detalle_factura"
                                        , 4, folio, articulo, cantidad
                                        , "0") != PGRES_TUPLES_OK) {
            res = PQexec(conn, "ROLLBACK");
        }
        //do {
            //vacia_buffer();
            printf("Seguir agregando articulo [S/n]: ");
            scanf("%c", &respuesta);
        //}while(respuesta != 'S' || respuesta != 's' || respuesta != 'N' || respuesta != 'n');
        //if (respuesta == 'S' || respuesta == 's') printf("\n");
        vacia_buffer();
    } while (respuesta == 'S' || respuesta == 's');

    res = PQexec(conn, "COMMIT");
    PQclear(res);

}


ExecStatusType agregar_detalle_factura(PGconn * conn, char * name_func_postgres, int cantidad, ...) {
	va_list lista_argumentos;
	va_start (lista_argumentos, cantidad);
	char * p_concatenado = " ";

	char * sql = "SELECT ";

	sql = cat_puntero(sql, name_func_postgres);
	sql = cat_puntero (sql, " ('");
	for (int i = 0; i < cantidad; i++) {
		sql = cat_puntero(sql, va_arg(lista_argumentos, char *));
		if ((i+1) == cantidad) 
			sql = cat_puntero(sql, "');");
		else
			sql = cat_puntero(sql, "', '");

	}

	va_end(lista_argumentos);

	PGresult * res = PQexec(conn, sql);

	printf("\n%s\n", sql);

    return PQresultStatus(res);

}
