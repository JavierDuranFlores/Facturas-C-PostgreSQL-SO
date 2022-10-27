#include <stdio.h>
#include <string.h>
//#include "../include/conexion.h"
/* #include "../include/leer.h"*/
#include "../include/agregar.h"
#include "../include/cliente.h"
#include "../include/articulo.h"
#include "../include/factura.h"
#include "../include/detalle_facturas.h"
#include "../include/actualizar.h"
#include "../include/eliminar.h"
/*#include "../include/cliente_telefonos.h"
#include "../include/articulo.h"
#include "../include/factura.h"
#include "../include/detalle_facturas.h"
#include "../include/service/cliente_service.h"
#include "../include/service/articulo_service.h"
#include "../include/service/factura_service.h"
#include "../include/service/detalle_factura_service.h"*/
#include "../include/next_line.h"
#include "../include/concat_punteros.h"


#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//#include <libpq-fe.h>

/*static PGconn * conexion;

PGconn * conexion_db();*/
void comprobar_estadodb();

/* MENUS */
//void menu_admin();
void menu_agregar();
void menu_leer();
void menu_actualizar();
void menu_actualizar_cliente();
void menu_actualizar_articulo();
void menu_actualizar_factura();


void menu_eliminar();

/*void mostrar_datos_factura();*/

void mostrar_tabla(char * tabla) ;
void servidor_cliente(char * sql) ;
void servidor_leer_factura(char * sql) ;
void servidor_leer_articulo(char * sql);
void servidor_leer_detalle_factura(char * sql);
Cliente * recolectar_datos_cliente();
Articulo * recolectar_datos_articulo();
Detalle_Facturas * recolectar_datos_detalle_factura();
Factura * recolectar_datos_factura();
/*int fd, fd1, fd2, fd3, fd4;
// FIFO file path
char * myfifo = "/tmp/myfifo"; //cliente -> (CRUD)
char * myfifo2 = "/tmp/myfifo2";
char * myfifo3 = "/tmp/myfifo3";
char * myfifo4 = "/tmp/myfifo4";
char * menu = "/tmp/menu";*/

int fdWR, fdRD;

char tabla[1024];

int main() {

    

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    /*mkfifo(myfifo, 0666);
    mkfifo(myfifo2, 0666);
    mkfifo(myfifo3, 0666);
    mkfifo(myfifo4, 0666);
    mkfifo(myfifo5, 0666);*/

    /*conn = conexion_db();
    agregar_detalle_factura_servicio(conn);*/
        int opcion = 0;
        char txt2[5];
        //conn = conexion_db();
        while(1) {

            printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Agregar    | 3. Leer     |");
        printf("\n| 2. Actualizar | 4. Eliminar |");
	printf("\n|	      5. Salir        |");
        printf("\n|---------------|-------------|");
            scanf("%i", &opcion);
            
            fdWR=open("servicios/menus",O_WRONLY);
            sprintf(txt2,"%i",opcion);
            write(fdWR,txt2,sizeof(txt2));
            printf("%s", txt2);
            close(fdWR);
            

        switch (opcion) {

		case 1:
			menu_agregar();
            printf("\n");
			break;
		case 2:
            menu_actualizar();
            printf("\n");
			break;
		case 3:
			menu_leer();
             printf("\n");
			break;
		case 4:
			menu_eliminar();
            printf("\n");
			break;
        case 5:
            main();
        break;
		default:
			printf("\nOpcion no disponible\n");

	}

        }
    
    /*
    //leer_todos(conn, "mostrar_clientes();");
    /*printf("\n");
    leer_todos(conn, "mostrar_clientes();");
    leer_todos(conn, "mostrar_facturas();");
    leer_todos(conn, "mostrar_detalle_facturas();");
    leer_todos(conn, "mostrar_articulos();");
	
    // AGREGAR CLIENTES
    /*struct Cliente * cliente= cliente_constructor ("Vanessa", "Benavidez", "2edd", "San Jose",  "28", "Mexico");  

    agregar_todos(conn, "insertar_cliente ", 6, cliente->nombre, cliente->apellido, cliente->rfc, cliente->direccion, cliente->edad, cliente->pais);

    // AGREGAR ARTICULOS
   struct Articulo * articulo = articulo_constructor ("Papel", "6", "2022/02/02", "100", "10");

   agregar_todos(conn, "insertar_articulos ", 5, articulo->descripcion, articulo->cantidad, articulo->fecha_ingreso, articulo->precio, articulo->descuento);

    // AGREGAR FACTURAS,
    struct Factura * factura = factura_constructor ("2022/02/02", "1400", "MIL UN CUATROCIENTOS", "20");
    agregar_todos (conn, "insertar_factura ", 4, factura->fecha_factura, factura->importe_total, factura->importe_letra, factura->id_cliente);

    // AGREGAR DETALLE FACTURAS
    struct Detalle_Facturas * detalle_facturas = detalle_facturas_constructor ("1", "2", "5", "0");
    agregar_todos(conn, "insertar_detalle_factura", 4, detalle_facturas->folio, detalle_facturas->id_articulo, detalle_facturas->cantidad, detalle_facturas->subtotal);

     AGREGAR CLIENTE TELEFONOS
    struct Cliente_Telefonos * cliente_telefonos = cliente_telefonos_constructor("9626302716","20");

    agregar_todos(conn, "insertar_cliente_telefonos", 2, cliente_telefonos->telefono, cliente_telefonos->id_cliente);
    */
    return 0;
}

void menu_agregar() {
    Cliente * nuevo;
    Articulo* articulo;  
    Factura * factura;
    char txt[5];  
    int opcion = 0; 
    char instruccion[100]=" ";
    fdWR=open("servicios/menus",O_WRONLY);

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);
        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);

        switch(opcion) {
            case 1:
                nuevo  = recolectar_datos_cliente();
                strcat(instruccion,agregar_todos("insertar_cliente", 6, nuevo->nombre, nuevo->apellido, nuevo->rfc, nuevo->direccion, nuevo->edad, nuevo->pais));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //agregar_todos("insertar_cliente", 6, nuevo->nombre, nuevo->apellido, nuevo->rfc, nuevo->direccion, nuevo->edad, nuevo->pais);
                //servidor_cliente(agregar_todos("insertar_cliente", 6, nuevo->nombre, nuevo->apellido, nuevo->rfc, nuevo->direccion, nuevo->edad, nuevo->pais));

            break;
            case 2:
                articulo  = recolectar_datos_articulo();
                strcat(instruccion,agregar_todos("insertar_articulos", 5, articulo->descripcion, articulo->cantidad,  articulo->fecha_ingreso, articulo->precio, articulo->descuento));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);

                //agregar_articulo_servicio(conn);
            break;
            case 3:
                factura  = recolectar_datos_factura();
                strcat(instruccion,agregar_todos("insertar_factura", 4, factura->fecha_factura, factura->importe_total, factura->importe_letra, factura->id_cliente));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //facturar_servicio(conn);
            break;
            case 4:
                //menu_admin();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }


}

void menu_leer() {
    vacia_buffer();
    char * sql = " ";
    int opcion = 0; 
    char txt[5];
    char instruccion[10024]=" ";
    char * tabla = " ";
    char columna [100]=" ";
    fdWR=open("servicios/menus",O_WRONLY);

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|      5. Detalle Factura     |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);
        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);
        printf("ddd\n");
//writ al sever
        switch(opcion) {
            case 1:
                /*fdWR = open("servicios/consulta", O_WRONLY);
                sql = "mostrar_clientes";
                write(fdWR, sql, sizeof(sql));
                close(fdWR);*/

                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, columna, sizeof(columna));
                //printf("sss%s", tabla);
                close(fdRD);

                printf("\n%s\n", columna);

                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, instruccion, sizeof(instruccion));
                tabla = cat_puntero(tabla, instruccion);
                //printf("sss%s", tabla);
                close(fdRD);
                mostrar_tabla(tabla);
                //leer_todos(conn, "mostrar_clientes", 'f');
                //servidor_cliente("mostrar_clientes");
                break;
            case 2:

                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, columna, sizeof(columna));
                //printf("sss%s", tabla);
                close(fdRD);

                printf("\n%s\n", columna);

                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, instruccion, sizeof(instruccion));
                tabla = cat_puntero(tabla, instruccion);
                //printf("sss%s", tabla);
                close(fdRD);
                mostrar_tabla(tabla);
                //leer_todos(conn, "mostrar_articulos", 'f');
                //servidor_leer_articulo("mostrar_articulos");
                printf("\n");
                break;
            case 3:
                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, columna, sizeof(columna));
                close(fdRD);
                printf("\n%s\n", columna);

                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, instruccion, sizeof(instruccion));
                tabla = cat_puntero(tabla, instruccion);
                close(fdRD);
                mostrar_tabla(tabla);
                printf("\n");
                break;
            case 5:
                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, columna, sizeof(columna));
                //printf("sss%s", tabla);
                close(fdRD);
                printf("\n%s\n", columna);

                fdRD = open("servicios/consulta", O_RDONLY);
                read(fdRD, instruccion, sizeof(instruccion));
                tabla = cat_puntero(tabla, instruccion);
                //printf("sss%s", tabla);
                close(fdRD);
                mostrar_tabla(tabla);
                //leer_todos(conn, "mostrar_detalle_facturas", 'f');
                //servidor_leer_detalle_factura("mostrar_detalle_facturas");
                printf("\n");
                break;
            default:
			    printf("\nOpcion no disponible\n");
        }


    //menu_admin();
}

void servidor_cliente(char * sql) {
    printf("    ---- CLIENTES ---\n");
    /*fd = open(myfifo, O_WRONLY);
    write(fd, sql, strlen(sql)+1);
    close(fd);

    fd = open(myfifo, O_RDONLY);
    read(fd, tabla, sizeof(tabla));
                
    close(fd);*/
    mostrar_tabla(tabla);

}

void servidor_leer_factura(char * sql) {
    printf("    ---- FACTURAS ---\n");
    /*fd1 = open(myfifo2, O_WRONLY);
    write(fd1, sql, strlen(sql)+1);
    close(fd1);

    fd1 = open(myfifo2, O_RDONLY);
    read(fd1, tabla, sizeof(tabla));
                
    close(fd1);*/
    mostrar_tabla(tabla);
    
}

void servidor_leer_articulo(char * sql) {
    printf("    ---- ARTICULOS ---\n");
    /*fd2 = open(myfifo3, O_WRONLY);
    write(fd2, sql, strlen(sql)+1);
    close(fd2);

    fd2 = open(myfifo3, O_RDONLY);
    read(fd2, tabla, sizeof(tabla));
                
    close(fd2);*/
    mostrar_tabla(tabla);
    
}

void servidor_leer_detalle_factura(char * sql) {
    printf("    ---- DETALLE FACTURAS ---\n");
    /*fd3 = open(myfifo4, O_WRONLY);
    write(fd3, sql, strlen(sql)+1);
    close(fd3);

    fd3 = open(myfifo4, O_RDONLY);
    read(fd3, tabla, sizeof(tabla));
                
    close(fd3);*/
    //mostrar_tabla(tabla);
    
}

void mostrar_tabla(char * tabla) {

    //printf("%s\n", tabla);

    char * fila = "\n";
    fila = strtok(tabla, ";");
    if(fila != NULL){
        while(fila != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            //printf("Token: %s\n", fila);
            printf("\n%s\n", fila);
            fila = strtok(NULL, ";");
            
        }
    }

}

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

Detalle_Facturas * recolectar_datos_detalle_factura(){

    //vacia_buffer();

    printf("Digite su folio de Factura: ");
    char * descripcion = nextLine();

    printf("Digite el Id de articulo: " );
	char * id_articulo = nextLine();

    printf("Digite la cantidad: ");
	char * cantidad = nextLine();

    printf("Digite el subtotal");
	char * subtotal = nextLine();

    return detalle_facturas_constructor ("3", id_articulo, cantidad, subtotal);

}

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

void menu_actualizar() {
    int opcion = 0;
    char txt[5];
    char instruccion[100]=" ";
    fdWR=open("servicios/menus",O_WRONLY);

        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';

        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Salir    |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);
        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);

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
                //menu_admin();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

}

void menu_actualizar_cliente() {
    int opcion = 0;
    char txt[5];
    char instruccion[100]=" ";
    fdWR=open("servicios/menus",O_WRONLY);
    char * nuevo = " ";
    char * columna;
    char * id = " ";
    char * tabla = "clientes";
    char * sql = "SELECT actualizar(";
    do {

        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';

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
        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);
        vacia_buffer();
        printf("Digite el id cliente: ");
        id = nextLine();
        
        switch(opcion) {
            case 1:
                columna="nombre";
                printf("Digite su nombre: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //servidor_cliente(actualizar_todos("actualizar", 1, cadena));
                //actualizar_cliente_servicio(conn, "nombre");
            break;
            case 2:
                columna="rfc";
                printf("Digite su rfc: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_cliente_servicio(conn, "rfc");
            break;
            case 3:
                columna="edad";
                printf("Digite su edad: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_cliente_servicio(conn, "edad");
            break;
            case 4:
                columna="apellidos";
                printf("Digite sus apellidos: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_cliente_servicio(conn, "apellidos");
            break;
            case 5:
                columna="direccion";
                printf("Digite su direccion: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_cliente_servicio(conn, "direccion");
            break;
            case 6:
                columna="pais";
                printf("Digite su pais: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_cliente_servicio(conn, "pais");
            break;
            case 7:
                //menu_actualizar();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

void menu_actualizar_articulo() {
    int opcion = 0;
    char txt[5];
    char instruccion[100]=" ";
    char * nuevo = " ";
    char * columna;
    char * id = " ";
    char * tabla = "articulos";
    fdWR=open("servicios/menus",O_WRONLY);
    do {
        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';
        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. descripcion| 4. precio   |");
        printf("\n| 2. cantidad   | 5. descuento|");
        printf("\n| 3. F. Ingreso | 6. regresar |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);
        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);
        vacia_buffer();
        printf("Digite el id cliente: ");
        id = nextLine();

        switch(opcion) {
            case 1:
                columna="descripcion";
                printf("Digite su descripcion: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_articulo_servicio(conn, "descripcion");
            break;
            case 2:
                columna="cantidad";
                printf("Digite su cantidad: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_articulo_servicio(conn, "cantidad");
            break;
            case 3:
                columna="fecha_ingreso";
                printf("Digite su fecha ingreso: [A-M-D]");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_articulo_servicio(conn, "fecha_ingreso");
            break;
            case 4:
                columna="precio";
                printf("Digite su precio: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_articulo_servicio(conn, "precio");
            break;
            case 5:
                columna="descuento";
                printf("Digite su descuento: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_articulo_servicio(conn, "descuento");
            break;
            case 6:
                //menu_actualizar();
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

void menu_actualizar_factura() {
    int opcion = 0;
    char txt[5];
    char instruccion[100]=" ";
    char * nuevo = " ";
    char * columna;
    char * id = " ";
    char * tabla = "facturas";
    fdWR=open("servicios/menus",O_WRONLY);
    do {
        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';

        printf("\n|------------------------------|");
        printf("\n|             * Menu *         |");
        printf("\n|------------------------------|");
        printf("\n| 1. F. Factura | 3. Importe L.|");
        printf("\n| 2. Importe T. | 4. Id Cliente|");
        printf("\n|         5. regresar          |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);
        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);
        vacia_buffer();
        printf("Digite el folio de la factura: ");
        id = nextLine();


        switch(opcion) {
            case 1:
                columna="fecha_fact";
                printf("Digite fehca de la factura: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_factura_servicio(conn, "fecha_fact");
            break;
            case 2:
                columna="importe_total";
                printf("Digite el importe total: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_factura_servicio(conn, "importe_total");
            break;
            case 3:
                columna="importe_letra";
                printf("Digite el importe letra: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_factura_servicio(conn, "importe_letra");
            break;
            case 4:
                columna="id_cliente";
                printf("Digite el id cliente: ");
                nuevo = nextLine();
                strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                //actualizar_factura_servicio(conn, "id_cliente");
            break;
            case 5:
                //menu_actualizar();
            break;
            default:
			        printf("\nOpcion no disponible\n");
        }

    } while (opcion != 6);
}

void menu_eliminar() {
    int opcion = 0;
    char txt[5];
    char * id;
    char instruccion[100]=" ";
    char * idPun;
    fdWR=open("servicios/menus",O_WRONLY);
    do {
        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';
        printf("\n|-----------------------------|");
        printf("\n|            * Menu *         |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Cliente    | 3. Factura  |");
        printf("\n| 2. Articulo   | 4. Regresar |");
        printf("\n|---------------|-------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);

        sprintf(txt,"%i",opcion);
        printf(">>>>>>>%s\n",txt);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);        
        vacia_buffer();
        switch(opcion) {
            case 1:
                printf("Digite el id cliente: ");
                id = nextLine();
                strcat(instruccion, eliminar_todos("eliminar_cliente", 1, id));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
                printf("\n");
            break;
            case 2:
                printf("Digite el id articulo: ");
                id = nextLine();
                strcat(instruccion, eliminar_todos("eliminar_articulo", 1, id));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
            break;
            case 3:
                printf("Digite el id factura: ");
                id = nextLine();
                strcat(instruccion, eliminar_todos("eliminar_factura", 1, id));
                fdWR = open("servicios/consulta", O_WRONLY);
                write(fdWR, instruccion, sizeof(instruccion));
                close(fdWR);
            break;
            default:
			    printf("\nOpcion no disponible\n");
        }
    } while (opcion != 4);

}
/*
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

/*PGconn * conexion_db() {

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

}*/
