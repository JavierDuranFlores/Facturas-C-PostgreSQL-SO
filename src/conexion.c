#include "../include/conexion.h"
#include <stdlib.h>
#include <stdio.h>

static PGconn * conexion;
/*
PGconn * conexion_db() {

    if (conexion == NULL) {
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=market user=postgres password=Duran2001");
    }

    comprobar_estadodb(conexion);

    return conexion;
}
*/

/*void comprobar_estadodb() {

    if (PQstatus (conexion) == CONNECTION_BAD) {
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
    }

}*/

/*void do_exit(PGconn * conexion) {

    PQfinish(conexion);
    exit(1);

}*/

void do_exit_res(PGresult * res) {

   fprintf(stderr, "%s\n", PQerrorMessage(conexion));

    PQclear(res);
    exit(1);
 }
