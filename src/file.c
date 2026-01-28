#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "file.h"
#include "error.h"

/*---------------------------------------------*/

int file_exists(const char *path)
{
    if (!path) {
        error_set("file_exists: null path");
        return 0;
    }

    return access(path, F_OK) == 0;
}

/*---------------------------------------------*/

int file_create(const char *path)
{
    if (!path) {
        error_set("file_create: null path");
        return -1;
    }

    int fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd == -1) {
        error_set("file_create: could not create file");
        return -1;
    }

    close(fd);
    return 0;
}

/*---------------------------------------------*/

int file_delete(const char *path)
{
    if (!path) {
        error_set("file_delete: null path");
        return -1;
    }

    if (unlink(path) != 0) {
        error_set("file_delete: could not delete file");
        return -1;
    }

    return 0;
}

