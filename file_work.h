#ifndef FILE_WORK_H
#define FILE_WORK_H

#define FPATH_LEN 255

#define MARK "~=Simple C data file from 9-th lab. work=~01\n"

#define MARK_LEN (strlen(MARK) - 3)

int file_exist(char *path);

FILE* file_create(char* path);

FILE* file_open(char* path);

void file_close(FILE* file);

int file_remove(char* path);

#endif // FILE_WORK_H
