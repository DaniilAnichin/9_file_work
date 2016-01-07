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
#include <unistd.h>

#include "input_check.h"
#include "my_conio.h"

#define PATH_LEN 255

#define MARK "~=Simple C data file from 9-th lab. work=~01\n"

#define MARK_LEN (int)strlen(MARK) - 3

// Remake!
//void mkdirp(char* path)
//{
//    char* dir_cmd = NULL;
//    char* slash_pos = NULL;
//    char base_cmd[] = "mkdir -p ";

//    slash_pos = strrchr(path, '/');

//    if(slash_pos != NULL)
//    {
//        dir_cmd = (char*)calloc(strlen(base_cmd) + strlen(path) - \
//                                strlen(slash_pos), sizeof(char));
//        slash_pos[0] = '\0';
//        strcpy(dir_cmd, base_cmd);
//        strcat(dir_cmd, path);
//        system(dir_cmd);
//        slash_pos[0] = '/';
//    }
//}


char* get_basedir()
{
    char* basedir;
    char buff[PATH_LEN + 1];

    basedir = getcwd(buff, PATH_LEN + 1);

    return basedir;
}

int is_exist(char *path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}


FILE* file_create(char *path)
{
    FILE* to_create;

    int exist = 0;
    int rewrite = 0;
    int incorrect_choice = 0;

    char choice = 0;
    char* res_path = NULL;
    char buffer[BUFSIZ];

    exist = is_exist(path);



    if(exist)
    {
        printf("This file already exists; Rewrite? [y/n]\n");

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
            printf("Input another file name:\n");
            res_path = (char*)calloc(PATH_LEN, sizeof(char));
            string_input(stdin, PATH_LEN, res_path, 0);
            to_create = file_create(res_path);
            free(res_path);
        }
        else
        {
            if((to_create = fopen(path, "wt+")) == NULL)
                puts("Cannot create the file..\n");
            else
            {
                setbuf(to_create, buffer);
                fputs(MARK, to_create);
            }
        }

    }
    else
    {
        if((to_create = fopen(path, "wt+")) == NULL)
            puts("Cannot create the file..\n");
        else
        {
            setbuf(to_create, buffer);
            fputs(MARK, to_create);
        }
    }

    return to_create;
}


FILE* file_open(char *path)
{
    FILE* to_open;

    char check[MARK_LEN];
    char* mark = MARK;
    char buffer[BUFSIZ];

    int is_opened = 0;
    int exist = 0;

    exist = is_exist(path);

    if(exist)
    {
        chmod(path, 0600);

        is_opened = (to_open = fopen(path, "rt+")) != NULL;

        if(is_opened)
        {
            setbuf(to_open, buffer);
            fseek(to_open, 0L, SEEK_SET);
            fgets(check, MARK_LEN, to_open);
            check[MARK_LEN - 1] = '\n';
            is_opened = strncmp(check, mark, MARK_LEN);
            if(!is_opened)
                return to_open;
            else
                puts("\tIncorrect file..\n");
        }
    }
    else
        puts("\tNo such file or directory..\n");

    return NULL;
}


void file_close(FILE* file)
{
    fchmod(fileno(file), 0600);
    fclose(file);
}
