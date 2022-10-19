#include "../../include/service/articulo_service.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd3;
char * myfifo3 = "/tmp/myfifo3";  
static PGconn * conexion;
char * tabla = " ";

int main () {
    
    
    mkfifo(myfifo3, 0666);

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    while (1) {

     
        // First open in read only and read
        fd3 = open(myfifo3,O_RDONLY);
        char sql[1024];
        read(fd3, sql,sizeof(sql));
        if (strcmp(sql, "mostrar_articulos")==0);
        {
            tabla = leer_todos_enviar(conexion_db(),"mostrar_articulos", 'f');
        }
        close(fd3);
        
        fd3 = open(myfifo3,O_WRONLY);
        write(fd3, tabla, strlen(tabla)+1);
        close(fd3);

    }

}

/*Articulo * recolectar_datos_articulo(){

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