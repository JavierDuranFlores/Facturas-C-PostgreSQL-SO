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

