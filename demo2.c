#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void do_exit(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

void demo2() {
    PGconn *conn = PQconnectdb("host=127.0.0.1 user=postgres password=example");

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        do_exit(conn);
    }

    PGresult *res = PQexec(conn, "SELECT VERSION()");    

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("No data retrieved\n");        
        PQclear(res);
        do_exit(conn);
    }    

    printf("%s\n", PQgetvalue(res, 0, 0));
    
    PQclear(res);
    PQfinish(conn);

}

void demo1() {
    demo2();
}

int main() {
    demo1();
    return 0;
}
