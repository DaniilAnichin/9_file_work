#ifndef SORTING_H
#define SORTING_H

#include "product.h"

#define NAM_LEN 40
#define STR_LEN 80

#define NAME_F 0
#define PRICE_F 1
#define NUMB_F 2

product* product_read(FILE* data, int num_line);

void product_write(FILE* data, int num_line, product* to_write);

product* product_update(product* to_edit);

int deleting(FILE* data, int num_line);

int name_find(FILE* data, char* name); // need?

int insertion(FILE* data, int num_line, product* to_insert); // need?

int sorted_insert(FILE* data, product* to_insert);

void sorting(FILE* data, int field, int to_upper);

void random_fill(FILE* data, int num_line);

int file_read(FILE* data);

#endif // SORTING_H
