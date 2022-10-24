#ifndef ACTUALIZAR_H
#define ACTUALIZAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "concat_punteros.h"
#include "next_line.h"

void actualizar_todos(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...);
char * actualizar_todos_(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...);

#endif