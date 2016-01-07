// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        sorting.c
// Date:        2015.12.25
// Author:      Daniil Anichin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

#include "input_check.h"
#include "my_conio.h"

#define ESCAPE_SEQ " \\/"
#define MARK "~=Simple C data file from 9-th lab. work=~01\n"

#define MARK_LEN (int)strlen(MARK)
#define NAM_LEN 40
#define PRI_LEN 13
#define NUM_LEN 3
#define STR_LEN 80

#define NAME_F 0
#define PRICE_F 1
#define NUMB_F 2

#define TEMPLATE "|  %40s  | $  %le  | x  %d  |"
#define HEADER "|  Name of the product:                      |    Price:             | Number: |"


typedef struct
{
    char* name;
    double price;
    int number;
}product;


product product_input()
{
    product _product;

    char* _name = (char*)calloc(NAM_LEN + 1, sizeof(char));
    double _price = 0;
    int _number = 0;

    int errors = 0;

    printf("Input the name of the product"
           "(space, slash and backslash are forbidden):\n");
    do
    {
        string_input(stdin, NAM_LEN + 1, _name, 0);
        if((errors = (strpbrk(_name, ESCAPE_SEQ) != NULL)))
            printf("\tTry again, incorrect symbols\n");
    }while(errors);

    printf("Input the price of the single product:\n");
    _price = double_input(0, 9999);

    printf("Input the number of this product:\n");
    _number = integer_input(0, 999);


    _product.name = _name;
    _product.price = _price;
    _product.number = _number;

    return _product;
}


void product_output(product to_output)
{
    printf("|  ");
    printf("%-*.*s", NAM_LEN, NAM_LEN, to_output.name);
    printf("  | $  ");
    printf("%*.*le", PRI_LEN, PRI_LEN - 2, to_output.price);
    printf("  | x  ");
    printf("%*d", NUM_LEN, to_output.number);
    printf("  |");
    printf("\n");
}


product product_read(FILE* data, int num_line)
{
    product to_read;

    char* _name = (char*)calloc(NAM_LEN + 1, sizeof(char));
    double _price = 0;
    int _number = 0;

    int scanf_res = 0;

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);

    scanf_res = fscanf(data, TEMPLATE, _name, &_price, &_number);

    if(!(scanf_res == 3 && scanf_res != EOF))
       printf("0");

    to_read.name = _name;
    to_read.price = _price;
    to_read.number = _number;

    return to_read;
}


void product_write(FILE* data, int num_line, product to_write)
{
    /* Writes product data to the file, like
|  NameNameNameNameNameNameNameNameNameName  | $  PricePricePricePr  | x  Num  |
    */

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);

    fprintf(data, "|  ");
    fprintf(data, "%-*.*s", NAM_LEN, NAM_LEN, to_write.name);
    fprintf(data, "  | $  ");
    fprintf(data, "%*.*e", PRI_LEN, PRI_LEN - 2, to_write.price);
    fprintf(data, "  | x  ");
    fprintf(data, "%*d", NUM_LEN, to_write.number);
    fprintf(data, "  |");
    fprintf(data, "\n");

    fflush(data);
}


product product_edit(product to_edit)
{
    char* new_name = (char*)calloc(NAM_LEN + 1, sizeof(char));
    double new_price = 0;
    int new_number = 0;

    int errors = 0;
    int incorrect_choice = 1;
    char field_symb[] = "0";
    char cycle = 'y';
    while(cycle == 'y')
    {
        incorrect_choice = 1;

        printf("Which field to edit?[a - name, p - price, n - number]\n");
        while(incorrect_choice)
        {
            field_symb[0] = getche();
            if((incorrect_choice = (strpbrk(field_symb, "apn") == NULL)))
                printf("Unknown value: %c; repeat the choice\n", field_symb[0]);
        }

        switch(field_symb[0])
        {
        case 'a':
        {
            printf("Input the new name of the product"
                   "(space, slash and backslash are forbidden):\n");
            do
            {
                string_input(stdin, NAM_LEN + 1, new_name, 0);
                if((errors = (strpbrk(new_name, ESCAPE_SEQ) != NULL)))
                    printf("\tTry again, incorrect symbols\n");
            }while(errors);
            to_edit.name = new_name;
        }
            break;
        case 'p':
        {
            printf("Input the price of the single product:\n");
            new_price = double_input(0, 9999);
            to_edit.price = new_price;
        }
            break;
        case 'n':
        {
            printf("Input the number of this product:\n");
            new_number = integer_input(0, 999);
            to_edit.number = new_number;
        }
            break;
        }

        do
        {
            printf("Do you want to change something else?['y' - yes, 'n' - no]\n");
            cycle = getche();
            incorrect_choice = cycle != 'y' && cycle != 'n';
            if(incorrect_choice)
                printf("Unknown value: %c; repeat the choice\n", cycle);
        }while(incorrect_choice);
    }

    return to_edit;
}


long get_last_line(FILE* data)
{
    fpos_t end_pos;

    long last_line = 0;

    fseek(data, 0L, SEEK_END);
    fgetpos(data, &end_pos);
    last_line = (end_pos.__pos - MARK_LEN) / STR_LEN;

    return last_line;
}

int insertion(FILE* data, int num_line, product to_insert)
{
    product temp_prod;

    long last_line = 0;

    last_line = get_last_line(data);

    while(last_line >= num_line)
    {
        temp_prod = product_read(data, last_line);
        product_write(data, last_line + 1, temp_prod);
        last_line--;
    }

    product_write(data, num_line, to_insert);

    return 0;
}


int deleting(FILE* data, int num_line)
{
    product temp_prod;

    fpos_t end_pos;

    long last_line = 0;

    last_line = get_last_line(data);

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);

    for(num_line = 1; num_line < last_line + 1; num_line++)
    {
        temp_prod = product_read(data, num_line + 1);
        product_write(data, num_line, temp_prod);
    }

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);
    fgetpos(data, &end_pos);

    ftruncate(fileno(data), end_pos.__pos);

    return 0;
}


int name_exist(FILE* data, char* name)
{
    product to_compare;

    long last_line = 0;

    int is_exist = 0;
    int num_line = 0;

    last_line = get_last_line(data);

    for(num_line = 1; num_line < last_line + 1; num_line++)
    {
        to_compare = product_read(data, num_line);
        is_exist += !strcmp(name, to_compare.name);
        if(is_exist)
            return is_exist;
    }

    return is_exist;
}


int compare(product* first_prod, product* second_prod, int field)
{
    int result = 0;

    switch(field)
    {
    case NAME_F:
        result = strcmp(second_prod->name, first_prod->name);
        break;
    case PRICE_F:
        result = second_prod->price - first_prod->price;
        break;
    case NUMB_F:
        result = second_prod->number - first_prod->number;
        break;
    }

    return result;
}


int sorted_insert(FILE* data, product to_insert)
{
    product to_compare;

    long last_line = 0;

    int is_upper = 0;   // if the read is > to_insert
    int field = 0;
    int to_upper = 0;

    int num_line = 0;

    fseek(data, MARK_LEN - 3, SEEK_SET);
    field = fgetc(data) - '0';
    to_upper = fgetc(data) - '0';
    to_upper = to_upper == 0 ? -1 : 1;

    last_line = get_last_line(data);

    for(num_line = 1; num_line < last_line + 1; num_line++)
    {
        to_compare = product_read(data, num_line);
        is_upper = compare(&to_insert, &to_compare, field);

        if(is_upper * to_upper > 0)
            return insertion(data, num_line, to_insert);
    }

    return insertion(data, last_line + 1, to_insert);
}


void sorting(FILE* data, int field, int to_upper)
{
    product first_prod;
    product second_prod;

    long last_line = 0;

    int is_upper = 0;   // if the second is > first

    int i = 0;
    int j = 0;

    fseek(data, MARK_LEN - 3, SEEK_SET);
    fputc(field + '0', data);
    fputc((abs(to_upper) == to_upper) + '0', data);

    last_line = get_last_line(data);

    for(i = 1; i < last_line; i++)
        for(j = i; j < last_line + 1; j++)
        {
            first_prod = product_read(data, i);
            second_prod = product_read(data, j);
            is_upper = compare(&first_prod, &second_prod, field);

            if(is_upper * to_upper < 0)
            {
                product_write(data, j, first_prod);
                product_write(data, i, second_prod);
            }

        }
}


void random_fill(FILE* data, int num_line)
{
    product temp_prod;

    int line = 0;
    int letter = 0;
    int is_uniq = 0;

    temp_prod.name = (char*)calloc(STR_LEN, sizeof(char));

    srand(time(NULL));

    for(line = 0; line < num_line; line++)
    {
        is_uniq = 0;

        while(!is_uniq)
        {
            for(letter = 0; letter < 10; letter++)
                temp_prod.name[letter] = rand() % 26 + (int)'a';
            is_uniq = !name_exist(data, temp_prod.name);
        }

        temp_prod.price = (rand() % 9999) / (double)(rand() % 10 + 1);
        temp_prod.number = rand() % 999;

        sorted_insert(data, temp_prod);
    }
    free(temp_prod.name);
}


int file_read(FILE* data)
{
    product temp_prod;

    long last_line = 0;
    long num_line = 0;

    for(num_line = 1; num_line < last_line + 1; num_line++)
    {}
    return 0;
}
