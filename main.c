// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        main.c
// Date:        2015.12.25
// Author:      Daniil Anichin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

#include "input_check.h"
#include "my_conio.h"
#include "file_work.h"
#include "sorting.h"

#define TO_UP 1
#define TO_LOW -1

#define PATH_LEN 80

int is_exit = 0;

int start_run();

int file_run(FILE* data);

void alert(char* reason);

int main(void)
{
    start_run();

    return 0;
}

int start_run()
{
    FILE* work_file;

    char *start_menu[] = {
        "Create file;\n",
        "Open file;\n",
        "Read file;\n",
        "Delete file;\n",
        "Exit program;\n",
    };

    char menu_symb[] = "0";
    char random = '\0';
    char path[PATH_LEN + 1];
    char full_path[FPATH_LEN + 1];

    int fill_number = 0;
    int menu_count = 0;
    int incorrect_choice = 1;
    int exit = 0;

    do
    {
        system("clear");
        for(menu_count = 0; menu_count < 5; menu_count++)
            printf("%d) %s", menu_count + 1, start_menu[menu_count]);

        printf("Input the number of menu item:\n");
        while(incorrect_choice)
        {
            menu_symb[0] = getche();
            if(!strpbrk(menu_symb, "12345"))
                printf("Unknown value: %c; repeat the choice\n", menu_symb[0]);
            else
                incorrect_choice = 0;
        }

        switch(menu_symb[0])
        {
        case '1':
        {
            puts("Input the name of the file to create:");
            puts("(If you wish inner directories, "
                 "type them with '/' separator;");
            puts("Further this path may be appended "
                 "to executable's base dir)");
            string_input(stdin, PATH_LEN, path, 0);
            getcwd(full_path, FPATH_LEN + 1);
            strcat(full_path, "/");
            strcat(full_path, path);

            work_file = file_create(full_path);
            if(work_file)
            {
                incorrect_choice = 1;

                puts("Do you want to fill the file with random values?[Y/N]");
                while(incorrect_choice)
                {
                    random = getche();
                    if(!strpbrk(&random, "ynYN"))
                        printf("Unknown value: %c; repeat the choice\n",
                               random);
                    else
                        incorrect_choice = 0;
                }
                if(random == 'y' || random == 'Y')
                {
                    puts("Input the number of items to create:");
                    fill_number = integer_input(1, 200);
                    random_fill(work_file, fill_number);
                }

                file_run(work_file);
            }
        }
            break;
        case '2':
        {
            puts("Input the name of the file to open & operate with:");
            string_input(stdin, PATH_LEN, path, 0);
            getcwd(full_path, FPATH_LEN + 1);
            strcat(full_path, "/");
            strcat(full_path, path);

            if(!file_exist(full_path))
                alert("\tNo such file or directory;");
            else
            {
                work_file = file_open(full_path);
                if(work_file)
                    file_run(work_file);
            }
        }
            break;
        case '3':
        {
            puts("Input the name of the file to read:");
            string_input(stdin, PATH_LEN, path, 0);
            getcwd(full_path, FPATH_LEN + 1);
            strcat(full_path, "/");
            strcat(full_path, path);

            if(!file_exist(full_path))
                alert("\tNo such file or directory;");
            else
            {
                work_file = file_open(full_path);
                if(work_file)
                    file_read(work_file);
            }
        }
            break;
        case '4':
        {
            puts("Input the name of the file to delete:");
            string_input(stdin, PATH_LEN, path, 0);
            getcwd(full_path, FPATH_LEN + 1);
            strcat(full_path, "/");
            strcat(full_path, path);

            if(!file_exist(full_path))
                alert("\tNo such file or directory;");
            else
                if(remove(full_path))
                    alert("\tUnable to delete this file;");
        }
            break;
        case '5':
        {
            printf("Good luck;\n");
            exit = 1;
        }
            break;
        }
    }while(!exit);

    return menu_symb[0] - '0';
}


int file_run(FILE* data)
{
    product* work_product = NULL;
    char *file_menu[] = {
        "Show file data;\n",
        "Add record;\n",
        "Edit record;\n",
        "Sort records;\n",
        "Delete record;\n",
        "Save & close the file;\n"
    };

    char menu_symb[] = "0";
    char work_name[NAM_LEN + 1];

    int work_line = 0;
    int menu_count = 0;
    int incorrect_choice = 1;
    int exit = 0;

    do
    {
        incorrect_choice = 1;
        system("clear");
        for(menu_count = 0; menu_count < 6; menu_count++)
            printf("%d) %s", menu_count + 1, file_menu[menu_count]);

        printf("Input the number of menu item:\n");
        while(incorrect_choice)
        {
            menu_symb[0] = getche();
            if(!strpbrk(menu_symb, "123456"))
                printf("Unknown value: %c; repeat the choice\n", menu_symb[0]);
            else
                incorrect_choice = 0;
        }

        switch(menu_symb[0])
        {
        case '1':
        {
            file_read(data);
        }
            break;
        case '2':
        {
            work_product = product_input();
            if(work_product)
            {
                sorted_insert(data, work_product);
                product_destroy(work_product);
            }
        }
            break;
        case '3':
        {
            puts("Input the name of the product to edit:");
            string_input(stdin, NAM_LEN, work_name, 0);

            work_line = name_find(data, work_name);
            if(!work_line)
                alert("\tNo such product;");
            else
            {
                work_product = product_read(data, work_line);
                product_update(work_product);
                product_write(data, work_line, work_product);
                product_destroy(work_product);
            }
        }
            break;
        case '4':
        {

        }
            break;
        case '5':
        {
            puts("Input the name of the product to delete:");
            string_input(stdin, NAM_LEN, work_name, 0);

            work_line = name_find(data, work_name);
            if(!work_line)
                alert("\tNo such product;");
            else
                deleting(data, work_line);
        }
            break;
        case '6':
        {
            file_close(data);
            exit = 1;
        }
            break;
        }

    }while(!exit);

    return menu_symb[0] - '0';
}

void alert(char* reason)
{
    puts(reason);
    puts("Press any key to go back");
    getch();
}

/*
//int program_run()
{
    int menu_res = 0;

    menu_res = start_run();

    switch(menu_res)
    {
    case 1:
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
    case 2:
    {
        printf("Input the number of this product:\n");
        new_number = integer_input(0, 999);
        to_edit.number = new_number;
    }
        break;
    case 3:
    {
        printf("Input the number of this product:\n");
        new_number = integer_input(0, 999);
        to_edit.number = new_number;
    }
        break;
    case 4:
    {
        printf("Input the number of this product:\n");
        new_number = integer_input(0, 999);
        to_edit.number = new_number;
    }
        break;
    case 5:
        printf("Good luck;\n");
        break;
    }
}
*/
