#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "error.h"
#include "file.h"
#include "table.h"

struct Database {
    char *base_path;
    Table **tables;
    size_t table_count;
    int is_open;
};


Database *db_create(void)
{
    Database *db = malloc(sizeof(Database));
    if (!db)
        return NULL;

    db->base_path = NULL;
    db->tables = NULL;
    db->table_count = 0;
    db->is_open = 0;

    return db;
}

/*---------------------------------------------*/

int db_open(Database *db, const char *path)
{
    if (!db || !path) {
        error_set("db_open: invalid arguments");
        return -1;
    }

    if (db->is_open) {
        error_set("db_open: database already open");
        return -1;
    }

    db->base_path = string_dup(path);
    if (!db->base_path) {
        error_set("db_open: memory error");
        return -1;
    }

    db->is_open = 1;
    return 0;
}

/*---------------------------------------------*/

int db_close(Database *db)
{
    if (!db || !db->is_open) {
        error_set("db_close: database not open");
        return -1;
    }

    for (size_t i = 0; i < db->table_count; i++) {
        table_destroy(db->tables[i]);
    }

    free(db->tables);
    db->tables = NULL;
    db->table_count = 0;

    free(db->base_path);
    db->base_path = NULL;

    db->is_open = 0;

    return 0;
}

/*---------------------------------------------*/

void db_destroy(Database *db)
{
    if (!db)
        return;

    if (db->is_open)
        db_close(db);

    free(db);
}

/*---------------------------------------------*/

int db_create_table(Database *db, const char *name)
{
    if (!db || !name || !db->is_open) {
        error_set("db_create_table: invalid arguments");
        return -1;
    }

    for (size_t i = 0; i < db->table_count; i++) {
        if (strcmp(table_get_name(db->tables[i]), name) == 0) {
            error_set("db_create_table: table already exists");
            return -1;
        }
    }

    Table *table = table_create();
    if (!table)
        return -1;

    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s.tbl", db->base_path, name);

    if (table_open(table, fullpath) != 0) {
        table_destroy(table);
        return -1;
    }

    Table **new_tables = realloc(
        db->tables,
        sizeof(Table *) * (db->table_count + 1)
    );

    if (!new_tables) {
        table_destroy(table);
        return -1;
    }

    db->tables = new_tables;
    db->tables[db->table_count] = table;
    db->table_count++;

    return 0;
}

/*---------------------------------------------*/

Table *db_get_table(Database *db, const char *name)
{
    if (!db || !name)
        return NULL;

    for (size_t i = 0; i < db->table_count; i++) {
        if (strcmp(table_get_name(db->tables[i]), name) == 0)
            return db->tables[i];
    }

    return NULL;
}

/*---------------------------------------------*/

int db_drop_table(Database *db, const char *name)
{
    if (!db || !name)
        return -1;

    for (size_t i = 0; i < db->table_count; i++) {

        if (strcmp(table_get_name(db->tables[i]), name) == 0) {

            table_destroy(db->tables[i]);

            for (size_t j = i; j < db->table_count - 1; j++)
                db->tables[j] = db->tables[j + 1];

            db->table_count--;
            
            if (db->table_count == 0) {
                free(db->tables);
                db->tables = NULL;
            } 

            else {
                Table **new_tables = realloc(db->tables,
                    sizeof(Table *) * db->table_count);
                if (new_tables)
                    db->tables = new_tables;
            }

            return 0;
        }
    }

    return -1;
}

