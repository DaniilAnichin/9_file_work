// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        main.c
// Date:        2015.12.25
// Author:      Daniil Anichin

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>

#include "file_work.h"
#include "sorting.h"

#define NAME_F 0
#define PRICE_F 1
#define NUMB_F 2

#define TO_UP 1
#define TO_LOW -1

int is_exit = 0;

size_t getFilesize(const char* filename)
{
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

int main(void)
{

    FILE* a;

    char path[] = "to/file2.txt";

    product exs;

//    a = fopen(path, "rt");
//            fclose(a);


//    exs = product_input();

//    product_output(exs);

//    product_write(a, 1, exs);
//    product_write(a, 2, exs);

//    if(a != NULL)
//    {
//        exs = product_read(a, 1);
//        product_output(exs);
//        exs = product_read(a, 2);
//        product_output(exs);
//        file_close(a, path);
//    }
//    else
//        printf("Trouble..\n");
//    a = file_open(path);
    a = file_create(path);
    if(a != NULL)
    {
        random_fill(a, 75);
//        exs = product_input();
//        exs = product_read(a, 1);
//        exs = product_edit(exs);
//        sorting(a, PRICE_F, TO_UP);
//        if(!name_exist(a, exs.name))
//            sorted_insert(a, exs);
//        deleting(a, 3);
//        product_write(a, 1, exs);
//        product_write(a, 2, exs);
//        product_write(a, 1, exs);
        file_close(a);
//        remove(path);
    }
    else
        printf("Trouble..\n");

//    printf("%ld\n", (long)getFilesize(path));
    return 0;
}

//int start_run()
//{
//    char start_menu = {
//        "Create file;\n",
//        "Open file;\n",
//        "Read file;\n",
//        "Delete file;\n",
//        "Exit program;\n",
//    };

//    int i = 0;

//    for(i = 0; i < 5; i++)
//        printf("%d) %s", i + 1, start_menu[i]);


//    char* path = (char*)calloc(PATH_LEN, sizeof(char));
//    double new_price = 0;
//    int new_number = 0;

//    int errors = 0;
//    int incorrect_choice = 1;
//    char menu_symb[] = "0";

//    printf("Input the number of menu item:\n");
//    while(incorrect_choice)
//    {
//        menu_symb[0] = getche();
//        if((incorrect_choice = (strpbrk(menu_symb, "12345") == NULL)))
//            printf("Unknown value: %c; repeat the choice\n", menu_symb[0]);
//    }

//    switch(menu_symb[0])
//    {
//    case '1':
//    {
//        printf("Input the new name of the product"
//               "(space, slash and backslash are forbidden):\n");
//        do
//        {
//            string_input(stdin, NAM_LEN + 1, new_name, 0);
//            if((errors = (strpbrk(new_name, ESCAPE_SEQ) != NULL)))
//                printf("\tTry again, incorrect symbols\n");
//        }while(errors);
//        to_edit.name = new_name;
//    }
//        break;
//    case '2':
//    {
//        printf("Input the number of this product:\n");
//        new_number = integer_input(0, 999);
//        to_edit.number = new_number;
//    }
//        break;
//    case '3':
//    {
//        printf("Input the name of the file to delete:\n");
//        string_input(stdin, PATH_LEN, path, 0);
//        if(!is_exist(path))
//        if(remove(path))
//    }
//        break;
//    case '4':
//    {
//        printf("Input the name of the file to delete:\n");
//        string_input(stdin, PATH_LEN, path, 0);
//        if(!is_exist(path))

//        if(remove(path))
//    }
//        break;
//    case '5':
//    {
//        printf("Good luck;\n");
//        is_exit = 1;
//    }
//        break;
//    }

//    return menu_symb[0] - '0';
//}



/*

//int file_run()
{
    char file_menu = {
        "Show file data;\n",
        "Add record;\n",
        "Edit record;\n",
        "Sort records;\n",
        "Delete record;\n",
        "Save & close the file;\n"
    };

}


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
