#ifndef MYSQL_CLI_H
#define MYSQL_CLI_H

#include <mysql/mysql.h>


MYSQL* connect_to_mysql();
void execute_query(MYSQL *conn, const char *query);
void cli_loop(MYSQL *conn);

#endif
