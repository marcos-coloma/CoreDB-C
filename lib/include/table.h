#ifndef TABLE_H
#define TABLE_H

#include "schema.h"

typedef struct Table Table;
typedef struct Record Record;

/* lifecycle */
Table *table_create(void);
void table_destroy(Table *table);

/* open/close */
int table_open(Table *table, const char *name);
int table_close(Table *table);

/* CRUD */
int table_insert(Table *table, const Record *rec);
int table_read(Table *table, int index, Record *out);
int table_update(Table *table, int index, const Record *rec);
int table_delete(Table *table, int index);

const char *table_get_name(const Table *table);
int table_record_count(Table *table);

#endif
