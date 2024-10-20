#ifndef ROW_H
#define ROW_H

#include <mysql/mysql.h>


void print_row(MYSQL_ROW row, unsigned int num_fields, unsigned int *max_widths);

#endif
