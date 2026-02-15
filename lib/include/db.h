#ifndef DB_H
#define DB_H

struct Database {
    char *path;
    int is_open; 
};

int db_open(struct Database *db, const char *path);
int db_close(struct Database *db);

int db_create_table(struct Database *db, const char *table_name);
int db_drop_table(struct Database *db, const char *table_name);


#endif