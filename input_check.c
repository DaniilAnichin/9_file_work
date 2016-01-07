// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        input_check.c
// Date:        2015.11.20
// Author:      Daniil Anichin

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#ifndef INFINITY
#define INFINITY 1.79769e+308
#endif


void string_input(FILE* stream, int str_len, char *output, int with_nl)
{
    int errors = 0;
    do
    {
        errors = 0;
        if(!fgets(output, str_len + 1, stream) ||\
                ((int)strlen(output) == str_len && output[str_len - 1] != '\n'))
        {
            output[str_len] = '\n';
            if(getchar() != '\n')
            {
                while(getchar() != '\n');
                printf("\tYou've inputed too many symbols, try again\n");
                errors = 1;
            }
        }
    }while(errors);

    if(!with_nl)
        output[(int)strlen(output) - 1] = '\0';
}


int old_integer_input(char* direction, int lower, int upper)
{
    /* Function to check if inputed number is an integer between
     * lower and upper */
    double recieved;
    short errors;

    // Simple check for inputing values
    do
    {
        errors = 0;
        recieved = INFINITY;
        printf("%s", direction);
        printf("(May be an integer number between %d and %d)\n", lower, upper);
        if(!scanf("%lf", &recieved) || getchar() != '\n')
        {
            printf("\tYou have entered not a numeric value!(string, maybe)\n");
            while(getchar() != '\n'){;}
            errors = 1;
        }
        if((int)recieved != recieved && recieved != INFINITY)
        {
            printf("\tYou have entered not an integer number!\n");
            errors = 1;
        }
        if(recieved > upper && recieved != INFINITY)
        {
            printf("\tThis number is too high(less than %d required)\n", upper + 1);
            errors = 1;
        }
        if(recieved < lower)
        {
            printf("\tThis number is too small(more than %d required)\n", lower - 1);
            errors = 1;
        }
    }
    while(errors);
    return (int)recieved;
}


double old_double_input(char* direction, double lower, double upper)
{
    /* Function to check if inputed number is an float(double, actually)
     * between lower and upper */
    double recieved = 0;
    short errors = 0;

    // Simple check for inputing values
    do
    {
        errors = 0;
        recieved = 1;
        printf("%s", direction);
        printf("(May be a float number between %.6g and %.6g)\n", lower, upper);
        if(!scanf("%lf", &recieved) || getchar() != '\n')
        {
            printf("\tYou have entered not a numeric value!(string, maybe)\n");
            while(getchar() != '\n');
            errors = 1;
        }
        if(recieved >= upper)
        {
            printf("\tThis number is too high(less than %.6g required)\n", upper);
            errors = 1;
        }
        if(recieved <= lower)
        {
            printf("\tThis number is too small(more than %.6g required)\n", lower);
            errors = 1;
        }
    }
    while(errors);
    return recieved;
}


long int integer_input(long int lower, long int upper)
{
    /* Function to check if inputed number is an integer between
     * lower and upper */
    const int MAX_LEN = 310;
    long int recieved;
    short errors = 0;

    char c_recieved[MAX_LEN];
    char **end_ptr = (char**)calloc(1, sizeof(char*));

    end_ptr[0] = c_recieved;


    // Simple check for inputing values
    do
    {
        errors = 0;

        printf("Value may be an integer number between %ld and %ld, including\n",\
               lower, upper);

        if(!fgets(c_recieved, MAX_LEN + 1, stdin) ||\
            ((int)strlen(c_recieved) == MAX_LEN && c_recieved[MAX_LEN - 1] != '\n'))
        {
            c_recieved[MAX_LEN - 1] = '\n';
            if(getchar() != '\n')
            {
                while(getchar() != '\n');
                printf("\tYou've inputed too many symbols,some of them will lost\n");
                errors = 1;
            }
        }

        recieved = strtol(c_recieved, end_ptr, 10);
        if(*c_recieved == '\n')
        {
            printf("\tYou have entered nothing\n");
            errors = 1;
        }

        if((**end_ptr == '.' || **end_ptr == 'e') && !errors)
        {
            printf("\tYou have entered not an integer value!\n");
            errors = 1;
        }

        if(**end_ptr != '\n' && !errors)
        {
            printf("\tYou have entered not a correct numeric value!\n");
            errors = 1;
        }

        if(recieved > upper && !errors)
        {
            printf("\tThis number is too high(less than %ld required)\n", upper + 1);
            errors = 1;
        }
        if(recieved < lower && !errors)
        {
            printf("\tThis number is too small(more than %ld required)\n", lower - 1);
            errors = 1;
        }
    }
    while(errors);

    return recieved;
}


double double_input(double lower, double upper)
{
    /* Function to check if inputed value is an float(double, actually)
     * number between lower and upper */
    double recieved = INFINITY;
    const int MAX_LEN = 310;
    short errors = 0;

    char c_recieved[MAX_LEN];
    char **end_ptr = (char**)calloc(1, sizeof(char*));

    end_ptr[0] = c_recieved;

    // Simple check for inputing values
    do
    {
        errors = 0;
        // c_recieved = ..
        printf("Value may be a float number between %.6g and %.6g, excluding\n",\
               lower, upper);

        if(!fgets(c_recieved, MAX_LEN + 1, stdin) ||\
            ((int)strlen(c_recieved) == MAX_LEN && c_recieved[MAX_LEN - 1] != '\n'))
        {
            c_recieved[MAX_LEN - 1] = '\n';
            if(getchar() != '\n')
            {
                while(getchar() != '\n');
                printf("You've inputed more symbols than double can contain,"
                       " exstra symbols will lost\n");
                errors = 1;
            }
        }

        recieved = strtod(c_recieved, end_ptr);

        if(*c_recieved == '\n')
        {
            printf("\tYou have entered nothing\n");
            errors = 1;
        }

        if(**end_ptr != '\n')
        {
            printf("\tYou have entered not a correct numeric value!\n");
            errors = 1;
        }

        if(recieved >= upper && !errors)
        {
            printf("\tThis number is too high(less than %.6g required)\n", upper);
            errors = 1;
        }
        if(recieved <= lower && !errors)
        {
            printf("\tThis number is too small(more than %.6g required)\n", lower);
            errors = 1;
        }
    }
    while(errors);

    return recieved;
}
