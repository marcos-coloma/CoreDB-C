#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "error.h"
#include "file.h"


int db_open(struct Database *db, const char *path)
{
    if (!db || !path) {
        error_set("db_open: invalid arguments");
        return -1;
    }

    if (!file_exists(path)) {
        if (file_create(path) != 0) {
            error_set("db_open: database could not be created");
            return -1;
        }
    }

    db->path = strdup(path);
    if (!db->path) {
        error_set("db_open: memory error");
        return -1;
    }

    db->is_open = 1;
    return 0;
}


int db_close(struct Database *db)
{
    if (!db || !db->is_open) {
        error_set("db_close: database not open");
        return -1;
    }

    free(db->path);
    db->path = NULL;
    db->is_open = 0;

    return 0;
}

