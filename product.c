// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        product.c
// Date:        2016.01.07
// Author:      Daniil Anichin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "product.h"
#include "input_check.h"

#define NAM_LEN 40
#define ESCAPE_SEQ " \\/"
#define WTEMPLATE "|  %-40s  | $  %.11e  | x  %3d  |\n"


product* product_create(const char* name, double price, int number)
{
    product* new_product = NULL;

    assert(name);

    new_product = (product*)calloc(1, sizeof(product));

    new_product->number = number;
    new_product->price  = price;
    new_product->name = (char*)calloc(NAM_LEN + 1, sizeof(char));

    strcpy(new_product->name, name);

    return new_product;
}


void product_destroy(product* waste_product)
{
    assert(waste_product);

    free(waste_product->name);
    free(waste_product);
}


product* product_input()
{
    product* work_product = NULL;

    char* name = (char*)calloc(NAM_LEN + 1, sizeof(char));
    double price = 0;
    int number = 0;

    int errors = 0;

    printf("Input the name of the product"
           "(space, slash and backslash are forbidden):\n");
    do
    {
        string_input(stdin, NAM_LEN + 1, name, 0);
        if((errors = (strpbrk(name, ESCAPE_SEQ) != NULL)))
            printf("\tTry again, incorrect symbols\n");
    }while(errors);

    printf("Input the price of the single product:\n");
    price = double_input(0, 9999);

    printf("Input the number of this product:\n");
    number = integer_input(0, 999);


    work_product = product_create(name, price, number);

    return work_product;
}


void product_output(product* work_product)
{
    printf(WTEMPLATE, work_product->name, work_product->price, work_product->number);
}
