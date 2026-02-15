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

#endif