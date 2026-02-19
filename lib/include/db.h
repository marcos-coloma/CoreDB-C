#ifndef DB_H
#define DB_H

#include "table.h"

typedef struct Database Database;

Database *db_create(void);
void db_destroy(Database *db);

int db_create_table(Database *db, const char *name);
int db_drop_table(Database *db, const char *name);
Table *db_get_table(Database *db, const char *name);

int db_open(Database *db, const char *path);
int db_close(Database *db);

size_t db_table_count(Database *db);
Table  *db_table_at(Database *db, size_t index);

#endif