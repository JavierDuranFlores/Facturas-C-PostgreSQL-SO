#include "../../include/service/detalle_factura_service.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd4;
char * myfifo4 = "/tmp/myfifo4";  
static PGconn * conexion;
char * tabla = " ";

int main () {
    
    
    mkfifo(myfifo4, 0666);

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    while (1) {

     
        // First open in read only and read
        fd4 = open(myfifo4,O_RDONLY);
        char sql[1024];
        read(fd4, sql,sizeof(sql));
        if (strcmp(sql, "mostrar_detalle_facturas")==0);
        {
            tabla = leer_todos_enviar(conexion_db(),"mostrar_detalle_facturas", 'f');
        }
        close(fd4);
        
        fd4 = open(myfifo4,O_WRONLY);
        write(fd4, tabla, strlen(tabla)+1);
        close(fd4);

    }

}


/*Detalle_Facturas * recolectar_datos_detalle_factura(){

    //vacia_buffer();

    /*printf("Digite su folio de Factura: ");
    char * descripcion = nextLine();

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
}*/

PGconn * conexion_db() {

    if (conexion == NULL) {
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=market user=postgres password=1234");
    }

    comprobar_estadodb();

    return conexion;
}

void comprobar_estadodb() {

    if (PQstatus (conexion) == CONNECTION_BAD) {
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
    }

}