#ifndef FILE_WORK_H
#define FILE_WORK_H

#define PATH_LEN 255

int is_exist(char *path);

FILE* file_create(char* path);

FILE* file_open(char* path);

void file_close(FILE* file);

#endif // FILE_WORK_H
