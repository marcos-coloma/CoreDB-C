#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "db.h"
#include "table.h"
#include "file.h"
#include "error.h"
#include "record.h"

struct Table {
    int fd;
    char name[256];
    int record_count;
};


Table *table_create(void)
{
    Table *table = malloc(sizeof(Table));
    if (!table)
        return NULL;

    table->fd = -1;
    table->record_count = 0;
    table->name[0] = '\0';

    return table;
}

/*---------------------------------------------*/

int table_open(Table *table, Database *db, const char *name)
{
    if (!table || !name || !db) return -1;

    strncpy(table->name, name, sizeof(table->name) - 1);
    
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s.tbl", db_get_base_path(db), name);

    if (!file_exists(fullpath)) {
        if (file_create(fullpath) != 0) {
            return -1;
        }
    }

    int fd = file_open_rw(fullpath);
    if (fd < 0) return -1;

    table->fd = fd;
    off_t size = lseek(fd, 0, SEEK_END);
    table->record_count = (size < 0) ? 0 : (size / RECORD_SIZE);

    return 0;
}
/*------------------------------------------*/

int table_close(Table *table)
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

/*------------------------------------------*/

int table_insert(Table *table, const Record *rec)
{
    if (!table || !rec) {
        error_set("table_insert: null table or record");
        return -1;
    }

    char buffer[RECORD_SIZE];
    memset(buffer, 0, RECORD_SIZE);

    for (int i = 0; i < NUM_FIELDS; i++) {
        const char *field = record_get_field(rec, i);
        if (field) {
            strncpy(buffer + 1 + i * MAX_FIELD_LEN, field, MAX_FIELD_LEN - 1);
        }
    }
    
    if (lseek(table->fd, 0, SEEK_END) < 0) {
    error_set("table_insert: failed to seek end");
    return -1;
}

    ssize_t written = write(table->fd, buffer, RECORD_SIZE);
    if (written != RECORD_SIZE) {
        error_set("table_insert: failed to write record");
        return -1;
    }

    table->record_count++;
    return 0;
}

/*------------------------------------------*/

int table_read(Table *table, int index, Record *out)
{
    if (!table || !out) {
        error_set("table_read: null table or record");
        return -1;
    }

    if (index < 0 || index >= table->record_count) {
        error_set("table_read: index out of range");
        return -1;
    }


    char buffer[RECORD_SIZE];
    off_t offset = index * RECORD_SIZE;

    if (lseek(table->fd, offset, SEEK_SET) < 0) {
        error_set("table_read: failed to seek");
        return -1;
    }

    ssize_t read_bytes = read(table->fd, buffer, RECORD_SIZE);
    if (read_bytes != RECORD_SIZE) {
        error_set("table_read: failed to read record");
        return -1;
    }

    if (buffer[0] == 1) {
        error_set("record deleted");
        return -1;
    }

    for (int i = 0; i < NUM_FIELDS; i++) {
        record_set_field(out, i, buffer + 1 + i * MAX_FIELD_LEN);
    }

    return 0;
}

/*------------------------------------------*/

int table_update(Table *table, int index, const Record *rec)
{
    if (!table || !rec) {
        error_set("table_update: null table or record");
        return -1;
    }

    if (index < 0 || index >= table->record_count) {
        error_set("table_update: index out of range");
        return -1;
    }

    char buffer[RECORD_SIZE];
    memset(buffer, 0, RECORD_SIZE);

    for (int i = 0; i < NUM_FIELDS; i++) {
        const char *field = record_get_field(rec, i);
        if (field) {
            strncpy(buffer + 1 + i * MAX_FIELD_LEN, field, MAX_FIELD_LEN - 1);
        }
    }

    off_t offset = index * RECORD_SIZE;

    if (lseek(table->fd, offset, SEEK_SET) < 0) {
        error_set("table_update: failed to seek");
        return -1;
    }

    ssize_t written = write(table->fd, buffer, RECORD_SIZE);
    if (written != RECORD_SIZE) {
        error_set("table_update: failed to write record");
        return -1;
    }

    return 0;
}

/*------------------------------------------*/

int table_delete(Table *table, int index)
{
    if (!table) {
        error_set("table_delete: null table");
        return -1;
    }

    if (index < 0 || index >= table->record_count) {
        error_set("table_delete: index out of range");
        return -1;
    }

    char buffer[RECORD_SIZE];
    memset(buffer, 0, RECORD_SIZE);

    buffer[0] = 1; 

    off_t offset = index * RECORD_SIZE;

    if (lseek(table->fd, offset, SEEK_SET) < 0) {
        error_set("table_delete: failed to seek");
        return -1;
    }

    ssize_t written = write(table->fd, buffer, RECORD_SIZE);
    if (written != RECORD_SIZE) {
        error_set("table_delete: failed to write delete flag");
        return -1;
    }

    return 0;
}

/*------------------------------------------*/

void table_destroy(Table *table)
{
    if (!table)
        return;

    if (table->fd >= 0)
        table_close(table);

    free(table);
}

/*------------------------------------------*/

const char *table_get_name(const Table *table)
{
    if (!table)
        return NULL;

    return table->name;
}

/*------------------------------------------*/

int table_record_count(Table *table)
{
    if (!table)
        return 0;
    return table->record_count;
}