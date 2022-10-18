#ifndef ACTUALIZAR_H
#define ACTUALIZAR_H

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <stdarg.h>

void actualizar_todos(PGconn * conn, char * name_func_postgres, int cantidad, ...);

#endif