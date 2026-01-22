#ifndef GAME_H
#define GAME_H

struct Database;

int db_open(struct Database *db, const char *path);
int db_close(struct Database *db);

int db_create_table(struct Database *db, const char *table_name);
int db_drop_table(struct Database *db, const char *table_name);


#endif