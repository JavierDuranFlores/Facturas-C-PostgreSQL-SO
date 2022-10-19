#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Lista {
    char * fila;
    struct Lista * sgte;
}Lista;



void agregar(char * fila);
void mostrar_lista();
void inicializar_lista();

#endif