#include "../include/concat_punteros.h"
char * cat_punteros(char * sql, int cantidad, ...) {

	va_list lista_argumentos;
        va_start (lista_argumentos, cantidad);
	char * p_concatenado = " ";
 
    	for (int i = 0; i < cantidad; i++) {
        	sql = cat_puntero(sql, va_arg(lista_argumentos, char *));
    		p_concatenado=cat_puntero(sql, "");
   	}
	va_end(lista_argumentos);

	return p_concatenado;
}

char * cat_puntero (char * p1, char * p2) {
	int i = 0;	
    char * p_concatenado = malloc(strlen(p1) + strlen(p2) + 1);

    while(*p1){
		p_concatenado[i++]=*p1++;
    }
    while(*p2){
     		p_concatenado[i++]=*p2++;
	}
	p_concatenado[i]='\0';

	return p_concatenado;
}
