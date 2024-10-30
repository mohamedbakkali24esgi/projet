#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/mysql_cli.h"
#include "table.h"
#include "row.h"





int main() {
    
    MYSQL *conn = connect_to_mysql(); 
    cli_loop(conn);  
    mysql_close(conn);
    return 0;
}
