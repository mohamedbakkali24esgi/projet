#include <stdio.h>
#include <mysql/mysql.h>
#include "row.h"


void print_row(MYSQL_ROW row, unsigned int num_fields, unsigned int *max_widths) {
    for (unsigned int i = 1; i < num_fields; i++) {
        printf("| %-*s ", max_widths[i], row[i] ? row[i] : "NULL");
    }
    printf("|\n");
}
