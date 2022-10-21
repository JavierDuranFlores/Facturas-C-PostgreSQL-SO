#include "../../include/agregar.h"
#include "../../include/concat_punteros.h"


//void agregar_todos(PGconn * conn, char * name_func_postgres, int cantidad, ...) {
char * agregar_todos(/*PGconn * conn, */char * name_func_postgres, int cantidad, ...) {
	va_list lista_argumentos;
	va_start (lista_argumentos, cantidad);
	char * p_concatenado = " ";

	char * sql = "SELECT ";

	sql = cat_puntero(sql, name_func_postgres);
	sql = cat_puntero (sql, " ('");
	/*sql = cat_puntero(sql, columna);
	sql = cat_puntero (sql, "', '");
	sql = cat_puntero (sql, nuevo);
	sql = cat_puntero (sql, "', '");
	sql = cat_puntero (sql, id);
	sql = cat_puntero (sql, "', '");
	sql = cat_puntero (sql, tabla);
	sql = cat_puntero (sql, "');");*/
	// SELECT func ('javier', 'ddd', 'jjjdjd');
	for (int i = 0; i < cantidad; i++) {
		sql = cat_puntero(sql, va_arg(lista_argumentos, char *));
		if ((i+1) == cantidad) 
			sql = cat_puntero(sql, "');");
		else
			sql = cat_puntero(sql, "', '");

	}

	va_end(lista_argumentos);

	//PGresult * res = PQexec(conn, sql);

	printf("\n%s\n", sql);
	return sql;
}

//SELECT actualizar ('nombre', 'javier', '1', 'clientes');
