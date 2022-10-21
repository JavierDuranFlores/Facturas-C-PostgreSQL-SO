#include "../../include/service/cliente_service.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fdMain, fdAgregar;
char txt[5];
char *myfifo = "/tmp/myfifo";
int fifoCliente;
int fifoServiceCliente;
// FIFO file path
static PGconn *conn;
char *tabla = " ";
 char txt2[5];
 //int i,j,fd1,fd2;
 int fdWR, fdRD;



int main()
{
    conn = conexion_db();   
    mkfifo("consulta",0666);	
    mkfifo("menuInicio",0666); 
    int opcion = 0;
   
    while (1)
    {
        
        fdWR= open("menuInicio",O_RDONLY);
        read(fdWR, txt, sizeof(txt));
        opcion = atoi(txt);
        close(fdWR);

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Agregar    | 3. Leer     |");
        printf("\n| 2. Actualizar | 4. Eliminar |");
	printf("\n|	      5. Salir        |");
        printf("\n|---------------|-------------|");
        printf("->%i\n", opcion);

        switch (opcion)     
        {

        case 1:
            menu_agregar();
            printf("\n");
            break;
        case 2:
            // menu_actualizar();
            printf("\n");
            break;
        case 3:
            //menu_leer();
            break;
        case 4:
            // menu_eliminar();
            printf("\n");
            break;
        case 5:
            main();
            break;
        default:
            printf("\nOpcion no disponible\n");
        }
    }

    // First open in read only and read
    /*fd1 = open(myfifo,O_RDONLY);
    char funcion[1024];
    char sql[1024];
    read(fd1, sql,sizeof(sql));
    if (strcmp(sql, "mostrar_clientes")==0)
        tabla = leer_todos_enviar(conexion_db(), "mostrar_clientes", 'f');
    else {
        PQexec(conexion_db(), sql);
        tabla="Cliente exitosamente ingresado";
    }
    printf("hj: %s\n", tabla);
    close(fd1);

    fd1 = open(myfifo,O_WRONLY);
    write(fd1, tabla, strlen(tabla)+1);
    close(fd1);*/
}

void menu_agregar() {
    int opcion = 0; 
    char instruccion[999] = " ";
    PGresult * res;
    mkfifo("menuAgregar",0666);
    fdRD=open("menuAgregar",O_RDONLY);
    read(fdRD,txt,sizeof(txt));

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|---------------|-------------|");
        opcion=atoi(txt);
        printf("-->%i\n",opcion);

        switch(opcion) {
            case 1:
            fdRD=open("consulta",O_RDONLY);
            read(fdRD,instruccion,sizeof(instruccion));
            printf("Con: %s\n",instruccion);
            PQexec(conn,instruccion);
            break;
            case 2:
                //agregar_articulo_servicio(conn);
            break;
            case 3:
                //facturar_servicio(conn);
            break;
            case 4:
                //menu_admin();
            break;
            default:
			    printf("\nOpcion no disponible\n");
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

PGconn *conexion_db()
{

    if (conn == NULL)
    {
        conn = PQconnectdb("host=127.0.0.1 port=5432 dbname=market user=postgres password=12345");
    }

    comprobar_estadodb();

    return conn;
}

void comprobar_estadodb()
{

    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage(conn));
    }
}
void do_exit_(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
    
    exit(1);
}
