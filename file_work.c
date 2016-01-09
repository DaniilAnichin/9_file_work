// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        file_work.c
// Date:        2015.12.25
// Author:      Daniil Anichin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "input_check.h"
#include "my_conio.h"
#include "file_work.h"


int file_exist(char* path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}


FILE* file_create(char* path)
{
    FILE* data_file;

    int exist = 0;
    int rewrite = 0;
    int incorrect_choice = 0;

    char choice = 0;
    char new_path[FPATH_LEN + 1];

    char* last_slash_pos = NULL;

    last_slash_pos = strrchr(path, '/');

    if(last_slash_pos != NULL)
    {
        last_slash_pos[0] = '\0';
        mkdir(path, 0755);
        last_slash_pos[0] = '/';
    }

    exist = file_exist(path);

    while(exist)
    {
        puts("This file already exists; Rewrite? [y/n]");

        do
        {
            choice = getche();
            incorrect_choice = choice != 'y' && choice != 'n';
            if(incorrect_choice)
            {
                printf("Unknown value: %c; repeat the choice\n", choice);
            }
        }while(incorrect_choice);

        rewrite = (choice == 'y') ? 1 : 0;

        if(!rewrite)
        {
            puts("Input another file name:");
            string_input(stdin, FPATH_LEN, new_path, 0);
            exist = file_exist(new_path);
        }
        else
            exist = 0;
    }

    data_file = fopen(path, "wt+");

    if(data_file == NULL)
        puts("\tCannot create the file..");
    else
        fputs(MARK, data_file);

    return data_file;
}


FILE* file_open(char *path)
{
    FILE* data_file = NULL;

    char check[MARK_LEN + 1];

    if(file_exist(path))
    {
        chmod(path, 0600);

        data_file = fopen(path, "rt+");

        if(data_file != NULL)
        {
            fseek(data_file, 0L, SEEK_SET);
            fgets(check, MARK_LEN + 1, data_file);

            if(strncmp(check, MARK, MARK_LEN))
            {
                puts("\tIncorrect file..");
                data_file = NULL;
            }
        }
    }
    else
        puts("\tNo such file or directory;");

    return data_file;
}


void file_close(FILE* file)
{
    fchmod(fileno(file), 0400);
    fclose(file);
}
