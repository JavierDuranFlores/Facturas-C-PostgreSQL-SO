#ifndef AGREGAR_H
#define AGREGAR_H

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <stdarg.h>

void agregar_todos(PGconn * conn, char * name_func_postgres, int cantidad, ...);


#endif
