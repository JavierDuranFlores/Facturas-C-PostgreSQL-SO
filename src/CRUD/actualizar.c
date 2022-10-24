#include "../../include/actualizar.h"

void actualizar_todos(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...) {
    va_list lista_argumentos;
	va_start (lista_argumentos, cantidad);
	char * p_concatenado = " ";

	char * sql = "SELECT ";

	sql = cat_puntero(sql, name_func_postgres);
	sql = cat_puntero (sql, " ('");

    for (int i = 0; i < cantidad; i++) {
		sql = cat_puntero(sql, va_arg(lista_argumentos, char *));
		if ((i+1) == cantidad)
			sql = cat_puntero(sql, "');");
		else
			sql = cat_puntero(sql, "', '");

	}

	va_end(lista_argumentos);

	printf("\n%s\n", sql);
}

char * actualizar_todos_(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...) {
    va_list lista_argumentos;
	va_start (lista_argumentos, cantidad);
	char * p_concatenado = " ";
	char * sql = "SELECT ";

	sql = cat_puntero(sql, name_func_postgres);
	sql = cat_puntero (sql, " ('");
	printf("dd\n");
    for (int i = 0; i < cantidad; i++) {
		sql = cat_puntero(sql, va_arg(lista_argumentos, char *));
		printf("%s\n", sql);
		if ((i+1) == cantidad)
			sql = cat_puntero(sql, "');");
		else
			sql = cat_puntero(sql, "', '");

	}
	printf("dd\n");

	va_end(lista_argumentos);

	//PGresult * res = PQexec(conn, sql);

	printf("\n%s\n", sql);
	p_concatenado = sql;
	return p_concatenado;
}