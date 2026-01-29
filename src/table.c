#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "table.h"
#include "file.h"
#include "error.h"
#include "record.h"


int table_open(struct Table *table, const char *name)
{
    if (!table || !name) {
        error_set("table_open: null table or name");
        return -1;
    }

    strncpy(table->name, name, sizeof(table->name) - 1);
    table->name[sizeof(table->name) - 1] = '\0';

    if (!file_exists(name)) {
        if (file_create(name) != 0) {
            return -1;
        }
    }

    int fd = file_open_write(name);
    if (fd < 0) return -1;

    table->fd = fd;

    int fd_read = file_open_read(name);
    if (fd_read < 0) return -1;

    off_t size = lseek(fd_read, 0, SEEK_END);
    file_close(fd_read);

    if (size < 0) {
        error_set("table_open: could not get file size");
        return -1;
    }

    table->record_count = size / RECORD_SIZE;

    return 0;
}

/*------------------------------------------*/

int table_close(struct Table *table)
{
    if (!table) {
        error_set("table_close: null table");
        return -1;
    }

    if (table->fd >= 0) {
        file_close(table->fd);
        table->fd = -1;
    }

    table->record_count = 0;
    table->name[0] = '\0';

    return 0;
}