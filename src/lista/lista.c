#include "../../include/lista/lista.h"

Lista * primeroL = NULL;
Lista * ultimoL = NULL;

void agregar(char * fila) {

    printf("%s\n", fila);

    Lista * nuevo = (Lista *) malloc(sizeof(Lista));

    nuevo -> fila = fila;

    if (primeroL== NULL) {
        primeroL = nuevo;
        primeroL -> sgte = NULL;
        ultimoL = nuevo;
    } else {
        ultimoL -> sgte = nuevo;
        nuevo -> sgte = NULL;
        ultimoL = nuevo;
    }

}

void mostrar_lista() {
    Lista * actual = NULL;
    actual = primeroL;

    if (primeroL != NULL) {
        while (actual != NULL) {
            printf("%s\n", actual->fila);
            actual = actual -> sgte;
        }
    }
}

void inicializar_lista() {
    primeroL = ultimoL = NULL;
}

