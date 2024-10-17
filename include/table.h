#ifndef TABLE_H
#define TABLE_H

#include <mysql/mysql.h>


void get_max_widths(MYSQL_RES *res, unsigned int *max_widths);
void print_table_header(MYSQL_RES *res, unsigned int *max_widths);
void print_table_separator(unsigned int num_fields, unsigned int *max_widths);

#endif
