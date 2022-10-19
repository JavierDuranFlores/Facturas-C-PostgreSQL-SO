#include "../../include/next_line.h"
#define MAX_MULT (120)

char * nextLine(void) {
  int chr = 0, mult = 0, len = 0;
  char *_c = NULL;

  while (1) {
    chr = fgetc(stdin);

    if (chr == EOF || chr == '\n') /* Detente solo si terminamos o si es final de linea */
      break;

    if (mult >= len) { /* pide más memoria si es necesario. */
      char *tmp = realloc(_c, mult + MAX_MULT);
      if (!tmp) /* si fall al pedir memoria, entonces detente ahora */
        break;
      _c = tmp, mult += MAX_MULT;
    }

    _c[len++] = chr; /* finalmente asigna. */
   }

  if (len)
    _c[len] = 0; /* pon el caracter nulo al final si no es NULL nuestra cadena */
  return _c; /* finalmente, devuelvela. */
}

void  vacia_buffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}