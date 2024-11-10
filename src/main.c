#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/mysql_cli.h"
#include "table.h"
#include "row.h"



void head(){
    printf(" __  __       _                              _    ____ _     ___ \n");
    printf("|  \\/  | ___ | |__   __ _ _ __ ___   ___  __| |  / ___| |   |_ _|\n");
    printf("| |\\/| |/ _ \\| '_ \\ / _` | '_ ` _ \\ / _ \\/ _` | | |   | |    | | \n");
    printf("| |  | | (_) | | | | (_| | | | | | |  __/ (_| | | |___| |___ | | \n");
    printf("|_|  |_|\\___/|_| |_|\\__,_|_| |_| |_|\\___|\\__,_|  \\____|_____|___|\n\n");
}

int main() {
    head();
    MYSQL *conn = connect_to_mysql(); 
    cli_loop(conn);  
    mysql_close(conn);
    return 0;
}
