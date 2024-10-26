#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/mysql_cli.h"

void get_password(char *password, size_t size) {
    printf("Enter MySQL password: ");
    if (fgets(password, size, stdin) == NULL) {
        perror("fgets failed");
        exit(EXIT_FAILURE);
    }
    password[strcspn(password, "\n")] = '\0'; 
}


void execute_query(MYSQL *conn, const char *query) {
    printf("Executing query: %s\n", query); 

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res) {
        unsigned int num_fields = mysql_num_fields(res);

        
        unsigned int *max_widths = malloc(num_fields * sizeof(unsigned int));

        
        get_max_widths(res, max_widths);

       
        mysql_data_seek(res, 0);

        
        print_table_header(res, max_widths);

        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            print_row(row, num_fields, max_widths);
        }

        
        print_table_separator(num_fields, max_widths);

        
        free(max_widths);
        mysql_free_result(res);
    } else if (mysql_field_count(conn) == 0) {
        printf("Query OK, %lld rows affected.\n", mysql_affected_rows(conn));
    }
}


MYSQL* connect_to_mysql() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    char host[256], user[256], password[256], database[256];
    unsigned int port = 3306;

    printf("Enter MySQL server address (e.g., localhost or IP): ");
    fgets(host, sizeof(host), stdin);
    host[strcspn(host, "\n")] = '\0';

    printf("Enter MySQL username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';

    get_password(password, sizeof(password));

    printf("Enter database name (or press Enter to skip): ");
    fgets(database, sizeof(database), stdin);
    database[strcspn(database, "\n")] = '\0';

    const char *db = strlen(database) > 0 ? database : NULL;

    if (mysql_real_connect(conn, host, user, password, db, port, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Connected to MySQL server at %s.\n", host);
    return conn;
}


void cli_loop(MYSQL *conn) {
    char *input;

    while (1) {
        
        input = readline("mysql> ");
        if (input == NULL) {
            break;  
        }

        if (strlen(input) > 0) {
            add_history(input);  

            
            if (strcmp(input, "exit") == 0) {
                free(input);
                break;
            }

            
            execute_query(conn, input);
        }

        free(input);
    }
}
