#ifndef DB_H
#define DB_H

typedef struct Database Database;

Database *db_create(void);
void db_destroy(Database *db);

int db_open(struct Database *db, const char *path);
int db_close(struct Database *db);

#endif