#include <stdio.h>
//#include "../include/conexion.h"
#include "../include/leer.h"
#include "../include/agregar.h"
#include "../include/cliente.h"
#include "../include/cliente_telefonos.h"
#include "../include/articulo.h"
#include "../include/factura.h"
#include "../include/detalle_facturas.h"
#include "../include/service/cliente_service.h"
#include "../include/service/articulo_service.h"
#include "../include/service/factura_service.h"
#include "../include/service/detalle_factura_service.h"

//#include <libpq-fe.h>

static PGconn * conexion;

PGconn * conexion_db();
void comprobar_estadodb();

/* MENUS */
void menu_admin();
void menu_agregar();
void menu_leer();
void menu_actualizar();
void menu_actualizar_cliente();
void menu_actualizar_articulo();
void menu_actualizar_factura();
void menu_eliminar();
void mostrar_datos_factura();

PGconn *conn;

int main() {
    /*conn = conexion_db();
    agregar_detalle_factura_servicio(conn);*/
    int opcion = 0;
    conn = conexion_db();
    do {

    	printf("\n|-----------------|");
    	printf("\n|    * Incio *    |");
    	printf("\n|-----------------|");
    	printf("\n| 1. Administrador|");
    	printf("\n| 2. Usuario      |");
    	printf("\n| 3. Salir        |");
    	printf("\n|-----------------|");
    	printf("\n\n Escoja una opcion: ");
	scanf("%d", &opcion);

	switch (opcion) {

		case 1:
			menu_admin();
			break;


	}

    } while (opcion != 3);

    //
    //leer_todos(conn, "mostrar_clientes();");
    /*printf("\n");
    leer_todos(conn, "mostrar_clientes();");
    leer_todos(conn, "mostrar_facturas();");
    leer_todos(conn, "mostrar_detalle_facturas();");
    leer_todos(conn, "mostrar_articulos();");
	*/
    // AGREGAR CLIENTES
    /*struct Cliente * cliente= cliente_constructor ("Vanessa", "Benavidez", "2edd", "San Jose",  "28", "Mexico");  
/*
    agregar_todos(conn, "insertar_cliente ", 6, cliente->nombre, cliente->apellido, cliente->rfc, cliente->direccion, cliente->edad, cliente->pais);*/

    // AGREGAR ARTICULOS
   /*struct Articulo * articulo = articulo_constructor ("Papel", "6", "2022/02/02", "100", "10");

   agregar_todos(conn, "insertar_articulos ", 5, articulo->descripcion, articulo->cantidad, articulo->fecha_ingreso, articulo->precio, articulo->descuento);*/

    // AGREGAR FACTURAS,
    /*struct Factura * factura = factura_constructor ("2022/02/02", "1400", "MIL UN CUATROCIENTOS", "20");
    agregar_todos (conn, "insertar_factura ", 4, factura->fecha_factura, factura->importe_total, factura->importe_letra, factura->id_cliente);*/

    // AGREGAR DETALLE FACTURAS
    /*struct Detalle_Facturas * detalle_facturas = detalle_facturas_constructor ("1", "2", "5", "0");
    agregar_todos(conn, "insertar_detalle_factura", 4, detalle_facturas->folio, detalle_facturas->id_articulo, detalle_facturas->cantidad, detalle_facturas->subtotal);*/

    // AGREGAR CLIENTE TELEFONOS
    /*struct Cliente_Telefonos * cliente_telefonos = cliente_telefonos_constructor("9626302716","20");

    agregar_todos(conn, "insertar_cliente_telefonos", 2, cliente_telefonos->telefono, cliente_telefonos->id_cliente);*/
   
    return 0;
}

void menu_admin() {
    int opcion = 0; 
    do { 
	printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Agregar    | 3. Leer     |");
        printf("\n| 2. Actualizar | 4. Eliminar |");
	printf("\n|	      5. Salir        |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

	switch (opcion) {

		case 1:
			menu_agregar();
			break;
		case 2:
            menu_actualizar();
			break;
		case 3:
			menu_leer();
			break;
		case 4:
			menu_eliminar();
			break;
        case 5:
            main();
        break;
		default:
			printf("\nOpcion no disponible\n");

	}

    } while(opcion != 5);
	    
}

void menu_agregar() {

    int opcion = 0; 
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                agregar_cliente_servicio(conn);
            break;
            case 2:
                agregar_articulo_servicio(conn);
            break;
            case 3:
                facturar_servicio(conn);
            break;
            case 4:
                menu_admin();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);

}

void menu_leer() {
    vacia_buffer();
    int opcion = 0; 
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|      5. Detalle Factura     |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                leer_todos(conn, "mostrar_clientes", 'f');
                break;
            case 2:
                leer_todos(conn, "mostrar_articulos", 'f');
                break;
            case 3:
                //mostrar_datos_factura();
                leer_todos(conn, "mostrar_facturas", 'f');
                break;
            case 5:
                leer_todos(conn, "mostrar_detalle_facturas", 'f');
                break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 4);

    menu_admin();
}

void menu_actualizar() {
    int opcion = 0;
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Salir    |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                menu_actualizar_cliente();
            break;
            case 2:
                menu_actualizar_articulo();
            break;
            case 3:
                menu_actualizar_factura();
            break;
            case 4:
                menu_admin();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}


void menu_actualizar_cliente() {
    int opcion = 0;
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. nombre     | 4. apellidos|");
        printf("\n| 2. rfc        | 5. direccion|");
        printf("\n| 3. edad       | 6. pais     |");
        printf("\n|          7. regresar        |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                actualizar_cliente_servicio(conn, "nombre");
            break;
            case 2:
                actualizar_cliente_servicio(conn, "rfc");
            break;
            case 3:
                actualizar_cliente_servicio(conn, "edad");
            break;
            case 4:
                actualizar_cliente_servicio(conn, "apellidos");
            break;
            case 5:
                actualizar_cliente_servicio(conn, "direccion");
            break;
            case 6:
                actualizar_cliente_servicio(conn, "pais");
            break;
            case 7:
                menu_actualizar();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

void menu_actualizar_articulo() {
    int opcion = 0;
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. descripcion| 4. precio   |");
        printf("\n| 2. cantidad   | 5. descuento|");
        printf("\n| 3. F. Ingreso | 6. regresar |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                actualizar_articulo_servicio(conn, "descripcion");
            break;
            case 2:
                actualizar_articulo_servicio(conn, "cantidad");
            break;
            case 3:
                actualizar_articulo_servicio(conn, "fecha_ingreso");
            break;
            case 4:
                actualizar_articulo_servicio(conn, "precio");
            break;
            case 5:
                actualizar_articulo_servicio(conn, "descuento");
            break;
            case 6:
                menu_actualizar();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

void menu_actualizar_factura() {
    int opcion = 0;
    do {

        printf("\n|------------------------------|");
        printf("\n|             * Menu *         |");
        printf("\n|------------------------------|");
        printf("\n| 1. F. Factura | 3. Importe L.|");
        printf("\n| 2. Importe T. | 4. Id Cliente|");
        printf("\n|         5. regresar          |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                actualizar_factura_servicio(conn, "fecha_fact");
            break;
            case 2:
                actualizar_factura_servicio(conn, "importe_total");
            break;
            case 3:
                actualizar_factura_servicio(conn, "importe_letra");
            break;
            case 4:
                actualizar_factura_servicio(conn, "id_cliente");
            break;
            case 5:
                menu_actualizar();
            break;
            default:
			        printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

void menu_eliminar() {
   int opcion = 0;
    do {

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                eliminar_cliente_servicio(conn);
            break;
            case 2:
                eliminar_articulo_servicio(conn);
            break;
            case 3:
                eliminar_factura_servicio(conn);
            break;
        }
    }while (opcion != 4);
    menu_admin();
}

void mostrar_datos_factura() {
    int opcion = 0;
    do {

        printf("\n|-----------------------------|");
        printf("\n|   * Mostrar Facturas Por *  |");
        printf("\n|-----------------------------|");
        printf("\n| 1. todas      | 4. cantidad |");
        printf("\n| 2. id cliente | 5. folio    |");
        printf("\n|          6. regresar        |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                leer_todos(conn, "vista_facturas_todas", 'v');
            break;
            case 2:
                actualizar_articulo_servicio(conn, "cantidad");
            break;
            case 3:
                actualizar_articulo_servicio(conn, "fecha_ingreso");
            break;
            case 4:
                actualizar_articulo_servicio(conn, "precio");
            break;
            case 5:
                actualizar_articulo_servicio(conn, "descuento");
            break;
            case 6:
                menu_actualizar();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

/* CONEXION A BASE DE DATOS  */

PGconn * conexion_db() {

    if (conexion == NULL) {
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=market user=postgres password=Duran2001");
    }

    comprobar_estadodb();

    return conexion;
}

void comprobar_estadodb() {

    if (PQstatus (conexion) == CONNECTION_BAD) {
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
    }

}