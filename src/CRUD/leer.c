#include "../../include/leer.h"

void do_exit(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

void leer_todos(PGconn * conn, char * name_funcion_postgres, char tipo) {
	char * sql = "SELECT * FROM ";
	sql = cat_puntero(sql, name_funcion_postgres);
	if (tipo == 'f')
		sql = cat_puntero(sql, "();");
	else if (tipo == 'v')
		sql = cat_puntero(sql, ";");
	//printf("%s\n", sql);
	PGresult * res = PQexec(conn, sql);
	vacia_buffer();

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("No se han recuperado los datos\n");
		PQclear(res);
		do_exit(conn);
	}
	int rows = PQntuples(res);
	int ncols = PQnfields(res);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < ncols; j++) {
			if ((j+1) == ncols)
				printf("|%10s|\n", PQgetvalue(res, i, j));
			else
				printf("|%10s| ", PQgetvalue(res, i, j));
		}
	}

	PQclear(res);
	//PQfinish(conn);	
}

char * leer_todos_enviar(PGconn * conn, char * name_funcion_postgres, char tipo) {
	char * tabla = " ";
	char * columna = " ";
	char * sql = "SELECT * FROM ";
	// SELECT * FROM mostrar_clientes
	sql = cat_puntero(sql, name_funcion_postgres);
	// SELECT * FROM mostrar_clientes
	if (tipo == 'f')
		sql = cat_puntero(sql, "();");
		// SELECT * FROM mostrar_clientes();
	else if (tipo == 'v')
		sql = cat_puntero(sql, ";");
	//printf("%s\n", sql);
	PGresult * res = PQexec(conn, sql);

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("No se han recuperado los datos\n");
		PQclear(res);
		do_exit(conn);
	}
	int rows = PQntuples(res);
	int ncols = PQnfields(res);
	for (int i=0; i<ncols; i++)
        columna = cat_puntero(columna, PQfname(res, i));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < ncols; j++) {
			if ((j+1) == ncols)
				tabla = cat_puntero(tabla, PQgetvalue(res, i, j));
				//printf("|%10s|\n", PQgetvalue(res, i, j));
			else
				tabla = cat_punteros(tabla, 2, PQgetvalue(res, i, j), " ");
				//rintf("|%10s| ", PQgetvalue(res, i, j));
		}
		if ((i+1) != rows)
		//cuando termina se pone ; para poder en el siguiente sustituir con ENTER
			tabla = cat_puntero(tabla, ";");
	}

	PQclear(res);

	return tabla;
	//PQfinish(conn);	
}

char * leer_todos_columnas(PGconn * conn, char * name_funcion_postgres) {

	char * columna = " ";
	char * sql = "SELECT * FROM ";
	// SELECT * FROM mostrar_clientes
	sql = cat_puntero(sql, name_funcion_postgres);
	sql = cat_puntero(sql, "();");
	//printf("%s\n", sql);
	PGresult * res = PQexec(conn, sql);

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("No se han recuperado los datos\n");
		PQclear(res);
		do_exit(conn);
	}
	int rows = PQntuples(res);
	int ncols = PQnfields(res);
	for (int i=0; i<ncols; i++)
        columna = cat_punteros(columna, 2, PQfname(res, i), " ");

	return columna;
}