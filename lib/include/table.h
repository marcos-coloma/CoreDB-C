#ifndef TABLE_H
#define TABLE_H

#include "record.h"

#define MAX_FIELD_LEN 64
#define NUM_FIELDS 9
#define RECORD_SIZE (NUM_FIELDS * MAX_FIELD_LEN)

typedef struct Table Table;

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

#endif
