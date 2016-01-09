// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        sorting.h
// Date:        2016.01.08
// Author:      Daniil Anichin

#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct
{
    char* name;
    double price;
    int number;
}product;

product* product_create(const char* name, double price, int number);

void product_destroy(product* waste_product);

product* product_input();

void product_output(product* to_output);

#endif // PRODUCT_H
