#ifndef RECORD_H
#define RECORD_H

#include "schema.h"

typedef struct Record Record;

Record *record_create(void);
void record_destroy(Record *rec);

int record_set_field(Record *rec, int index, const char *value);
const char *record_get_field(const Record *rec, int index);


#endif