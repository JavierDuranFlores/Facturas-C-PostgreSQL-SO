#ifndef CONCAT_PUNTEROS_H
#define CONCAT_PUNTEROS_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char * cat_punteros(char * sql, int cantidad, ...);
char * cat_puntero (char * p1, char * p2);

#endif
