#ifndef FILE_H
#define FILE_H


int file_exists(const char *path);
int file_create(const char *path);
int file_delete(const char *path);

int file_open_read(const char *path);
int file_open_write(const char *path);
void file_close(int fd);



#endif