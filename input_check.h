// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        input_check.h
// Date:        2015.11.20
// Author:      Daniil Anichin

#ifndef INPUT_CHECK_H
#define INPUT_CHECK_H

// Couple of functions to give you an ability to check input data
void string_input(FILE* stream, int str_len, char* output, int with_nl);

int old_integer_input(char* direction, int lower, int upper);

double old_double_input(char* direction, double lower, double upper);

long int integer_input(long int lower, long int upper);

double double_input(double lower, double upper);

#endif // INPUT_CHECK_H
