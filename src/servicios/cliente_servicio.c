#include "../../include/service/cliente_service.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd1;
char * myfifo = "/tmp/myfifo";  
int fifoCliente;
int fifoServiceCliente;
// FIFO file path
static PGconn * conexion;
char * tabla = " ";

int main () {
    
    
    mkfifo(myfifo, 0666);

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    while (1) {

     
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        char sql[1024];
        read(fd1, sql,sizeof(sql));
        if (strcmp(sql, "mostrar_clientes")==0);
        {
            tabla = leer_todos_enviar(conexion_db(), "mostrar_clientes", 'f');
        } 
        close(fd1);
        
        fd1 = open(myfifo,O_WRONLY);
        write(fd1, tabla, strlen(tabla)+1);
        close(fd1);

    }

}

/*Cliente * recolectar_datos_cliente(){

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