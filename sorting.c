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

#include "sorting.h"
#include "product.h"
#include "input_check.h"
#include "my_conio.h"

#define ESCAPE_SEQ " \\/"
#define MARK "~=Simple C data file from 9-th lab. work=~01\n"

#define MARK_LEN (int)strlen(MARK)

#define RTEMPLATE "|  %40s  | $  %le  | x  %d  |\n"
#define WTEMPLATE "|  %-40s  | $  %.11e  | x  %3d  |\n"
#define HEADER "|  Name of the product:                      |    Price:             | Number: |"


product* product_read(FILE* data, int num_line)
{
    product* work_product = NULL;

    char buffer[STR_LEN + 1];

    char name[NAM_LEN + 1];
    double price = 0;
    int number = 0;


    int scanf_res = 0;

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);
    fgets(buffer, STR_LEN + 1, data);
    scanf_res = sscanf(buffer, RTEMPLATE, name, &price, &number);

//    scanf_res = fscanf(data, RTEMPLATE, name, &price, &number);

    assert(scanf_res == 3 && scanf_res != EOF);

    work_product = product_create(name, price, number);

    return work_product;
}


void product_write(FILE* data, int num_line, product* to_write)
{
//  Writes product data to the file, with lenght up to 80 symbols, like
//|  Name...  | $  Price..  | x  Number  |
    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);

    fprintf(data, WTEMPLATE, to_write->name, to_write->price, to_write->number);

    fflush(data);
}


product* product_update(product* old_product)
{
    char new_name[NAM_LEN + 1];
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
            strcpy(old_product->name, new_name);
        }
            break;
        case 'p':
        {
            printf("Input the price of the single product:\n");
            new_price = double_input(0, 9999);
            old_product->price = new_price;
        }
            break;
        case 'n':
        {
            printf("Input the number of this product:\n");
            new_number = integer_input(0, 999);
            old_product->number = new_number;
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

    return old_product;
}


long get_last_line(FILE* data)
{
    fpos_t end_pos;

    long last_line = 0;

    fseek(data, 0L, SEEK_END);
    fgetpos(data, &end_pos);
    last_line = (end_pos.__pos - MARK_LEN) / (STR_LEN + 1);

    return last_line;
}

int insertion(FILE* data, int num_line, product* to_insert)
{
    // What about error return?
    product* temp_product = NULL;

    long last_line = 0;

    last_line = get_last_line(data);

    while(last_line >= num_line)
    {
        temp_product = product_read(data, last_line);
        product_write(data, last_line + 1, temp_product);
        last_line--;
    }

    product_write(data, num_line, to_insert);

    if(temp_product)
        product_destroy(temp_product);

    return 0;
}


int deleting(FILE* data, int num_line)
{
    product* temp_product = NULL;

    fpos_t end_pos;

    long last_line = 0;

    last_line = get_last_line(data);

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);

    for(num_line; num_line < last_line; num_line++)
    {
        temp_product = product_read(data, num_line + 1);
        product_write(data, num_line, temp_product);
    }

    fseek(data, MARK_LEN + (num_line - 1) * (STR_LEN + 1), SEEK_SET);
    fgetpos(data, &end_pos);

    ftruncate(fileno(data), end_pos.__pos);

    product_destroy(temp_product);

    return 0;
}


int name_find(FILE* data, char* name)
{
    product* check_product = NULL;

    long last_line = 0;

    int is_exist = 0;
    int num_line = 0;

    last_line = get_last_line(data);

    for(num_line = 1; num_line < last_line + 1; num_line++)
    {
        check_product = product_read(data, num_line);
        if(!strcmp(name, check_product->name))
            is_exist = num_line;
    }

    if(check_product)
        product_destroy(check_product);

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


int sorted_insert(FILE* data, product* to_insert)
{
    product* check_product = NULL;

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
        check_product = product_read(data, num_line);
        is_upper = compare(to_insert, check_product, field);

        if(is_upper * to_upper > 0)
            return insertion(data, num_line, to_insert);
    }

    if(check_product)
        product_destroy(check_product);

    return insertion(data, last_line + 1, to_insert);
}


void sorting(FILE* data, int field, int to_upper)
{
    product* first_product = NULL;
    product* second_product = NULL;

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
            first_product = product_read(data, i);
            second_product = product_read(data, j);
            is_upper = compare(first_product, second_product, field);

            if(is_upper * to_upper < 0)
            {
                product_write(data, j, first_product);
                product_write(data, i, second_product);
            }

        }

    product_destroy(first_product);
    product_destroy(second_product);
}


void random_fill(FILE* data, int num_line)
{
    product* temp_product = NULL;

    char name[STR_LEN + 1];
    double price = 0;
    int number = 0;

    int line = 0;
    int letter = 0;
    int is_uniq = 0;

    srand(time(NULL));

    for(line = 0; line < num_line; line++)
    {
        is_uniq = 0;

        while(!is_uniq)
        {
            for(letter = 0; letter < 10; letter++)
                name[letter] = rand() % 26 + (int)'a';
            name[letter] = '\0';
            is_uniq = !name_find(data, name);
        }

        price = (rand() % 9999) / (double)(rand() % 10 + 1);
        number = rand() % 999;

        temp_product = product_create(name, price, number);

        sorted_insert(data, temp_product);
    }

    product_destroy(temp_product);
}


int file_read(FILE* data)
{
    product* temp_product = NULL;

    long last_line = 0;
    long num_line = 0;
    int errors = 0;

    last_line = get_last_line(data);

    // which file?
    puts(HEADER);
    putc('\n', stdout);

    for(num_line = 1; num_line < last_line + 1; num_line++)
    {
        temp_product = product_read(data, num_line);

        if(!temp_product)
        {
            errors = 1;
            break;
        }
        product_output(temp_product);

        if(!(num_line % 20))
        {
            puts("Press any key to continue;");
            getch();
            system("clear");
            puts(HEADER);
            putc('\n', stdout);
        }
    }
    puts("Press any key to continue;");
    getch();

    if(temp_product)
        product_destroy(temp_product);

    return errors;
}
