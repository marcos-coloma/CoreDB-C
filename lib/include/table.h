#ifndef TABLE_H
#define TABLE_H

#include <unistd.h>
#include "record.h"

#define MAX_FIELD_LEN 64
#define NUM_FIELDS 9
#define RECORD_SIZE (NUM_FIELDS * MAX_FIELD_LEN)

typedef struct Table Table;


int table_open(struct Table *table, const char *name);
int table_close(struct Table *table);

int table_insert(struct Table *table, const struct Record *rec);
int table_read(struct Table *table, int index, struct Record *out);

int table_count(const struct Table *table);

int table_update(struct Table *table, int index, const struct Record *rec);
int table_delete(struct Table *table, int index);

#endif