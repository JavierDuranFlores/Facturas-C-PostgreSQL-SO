#ifndef LEER_H
#define LEER_H

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "../include/next_line.h"
#include "../../include/concat_punteros.h"

void leer_todos(PGconn * conn, char * name_funcion_postgres, char tipo);
void do_exit(PGconn *conn);

#endif
