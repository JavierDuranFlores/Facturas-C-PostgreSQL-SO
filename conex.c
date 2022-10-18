
#include <stdlib.h>
#include <libpq-fe.h>
#include <stdio.h>
//  FORMAS DE COMPILAR EL CODIGO
// gcc -o conex conexion.c -I /usr/include/postgresql/ -lpq
//gcc conexion.c -lpq -o cliente
// ./
char tab[50], cad[100];
int opc;

int main()
{
    PGconn *conn;
    PGresult *resultado;
    PGresult *ress;
    int i,j;
    conn=PQsetdbLogin("localhost","5432",NULL,NULL,"ejemplo","postgres","supervisor");
    //puts("Hola Mexico");
    
    if(PQstatus(conn) != CONNECTION_BAD)
      {  printf("CONEXION EXITOSA\n");
         resultado=PQexec(conn, "select *from cliente");
         printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
         if(resultado != NULL){
             printf("GUARDANDO LOS DATOS DE LOS CLIENTES\n");
             for (i = 0; i < PQntuples(resultado); i++){ //filas
                for (j = 0; j < PQnfields(resultado); j++){//columnas
                     printf("%s\t",PQgetvalue(resultado,i,j));
                   }
                   printf("\n");
               }
               
        /*sprintf(cad,"select * from alumnos");
        resultado = PQexec(conn, cad);
        */
        }
          //alta de un alumno
          /*char nom[50], matri[10],instrucc[100];
          printf("Dame su nombre");
          scanf("%s",&nom);
          printf("Dame su matricula");
          scanf("%s",&matri);
          sprintf(instrucc,"insert into clientes values('%s','%s')",nom,matri),
          PQexec(conn,instrucc);*/
     }
    else
        printf("error al conectar a la base de datos");
 return 0;
}
//-L/usr/local/include -lpq
//-L/usr/local/include -lpq
