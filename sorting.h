#ifndef SORTING_H
#define SORTING_H

typedef struct
{
    char* name;
    double price;
    int number;
}product;

product product_input();

void product_output(product to_output);

product product_read(FILE* data, int num_line);

void product_write(FILE* data, int num_line, product to_write);

product product_edit(product to_edit);

int deleting(FILE* data, int num_line);

int name_exist(FILE* data, char* name); // need?

int insertion(FILE* data, int num_line, product to_insert); // need?

int sorted_insert(FILE* data, product to_insert);

void sorting(FILE* data, int field, int to_upper);

void random_fill(FILE* data, int num_line);

int file_read(FILE* data);

#endif // SORTING_H
