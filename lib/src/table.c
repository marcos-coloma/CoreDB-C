#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "table.h"
#include "file.h"
#include "error.h"
#include "record.h"

/*---------------------------------------------*/

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

    int fd = file_open_rw(name);
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

/*------------------------------------------*/

int table_insert(struct Table *table, const struct Record *rec)
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
            strncpy(buffer + i * MAX_FIELD_LEN, field, MAX_FIELD_LEN - 1);
        }
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

int table_read(struct Table *table, int index, struct Record *out)
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

    record_init(out);
    for (int i = 0; i < NUM_FIELDS; i++) {
        record_set_field(out, i, buffer + i * MAX_FIELD_LEN);
    }

    return 0;
}

/*------------------------------------------*/

int table_update(struct Table *table, int index, const struct Record *rec)
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
            strncpy(buffer + i * MAX_FIELD_LEN, field, MAX_FIELD_LEN - 1);
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

int table_delete(struct Table *table, int index)
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
