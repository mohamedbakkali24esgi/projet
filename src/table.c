#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "table.h"

void get_max_widths(MYSQL_RES *res, unsigned int *max_widths) {
    unsigned int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);
    
    
    for (unsigned int i = 0; i < num_fields; i++) {
        max_widths[i] = strlen(fields[i].name);
    }

    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        for (unsigned int i = 0; i < num_fields; i++) {
            if (row[i]) {
                unsigned int len = strlen(row[i]);
                if (len > max_widths[i]) {
                    max_widths[i] = len;  
                }
            }
        }
    }
}


void print_table_header(MYSQL_RES *res, unsigned int *max_widths) {
    unsigned int num_fields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);

   
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("+");
        for (unsigned int j = 0; j < max_widths[i]+2; j++) {
            printf("-");  
        }
    }
    printf("+\n");

   
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("| %-*s ", max_widths[i], fields[i].name);
    }
    printf("|\n");

    
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("+");
        for (unsigned int j = 0; j < max_widths[i]+2; j++) {
            printf("-");  
        }
    }
    printf("+\n");
}
void print_table_separator(unsigned int num_fields, unsigned int *max_widths) {
    for (unsigned int i = 0; i < num_fields; i++) {
        printf("+");
        for (unsigned int j = 0; j < max_widths[i]+2; j++) {
            printf("-");  
        }
    }
    printf("+\n");
}