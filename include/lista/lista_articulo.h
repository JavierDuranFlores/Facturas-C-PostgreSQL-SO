#ifndef LISTA_ARTICULO_H
#define LISTA_ARTICULO_H

#include <stdio.h>
#include <stdlib.h>
#include "../../include/next_line.h"

typedef struct Lista_Articulo {

    char * articulo;
    char * cantidad;
    struct Lista_Articulo * sgte;

}Lista_Articulo;

//Lista_Articulo * primero, * ultimo;

Lista_Articulo * crear_articulo();
void agregar_articulo();
void mostrar_articulo();
void limpiar_lista();


#endif