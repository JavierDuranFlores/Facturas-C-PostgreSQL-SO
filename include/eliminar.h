#ifndef ELIMINAR_H
#define ELIMINAR_H

#include <stdio.h>
#include <stdlib.h>
//#include <libpq-fe.h>
#include <stdarg.h>
#include "../include/concat_punteros.h"

//void eliminar_todos(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...);
char * eliminar_todos(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...);


#endif