#ifndef CONEXION_H
#define CONEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

//PGconn * conexion_db();
//void comprobar_estadodb();
//void do_exit(PGconn * conexion);
void do_exit_res(PGresult * res);

#endif
