#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "error.h" 

struct Record {
    char *fields[NUM_FIELDS];
};


Record *record_create(void)
{
    Record *rec = malloc(sizeof(Record));
    if (!rec)
        return NULL;

    for (int i = 0; i < NUM_FIELDS; i++)
        rec->fields[i] = NULL;

    return rec;
}

/*---------------------------------------------*/

int record_set_field(Record *rec, int index, const char *value) {
    if (!rec) {
        error_set("record_set_field: null record pointer");
        return -1;
    }

    if (index < 0 || index >= NUM_FIELDS) {
        error_set("record_set_field: index out of range");
        return -1;
    }

    if (rec->fields[index]) {
        free(rec->fields[index]);
    }


    if (value) {
        rec->fields[index] = string_dup(value);
        if (!rec->fields[index]) {
            error_set("record_set_field: memory error");
            return -1;
        }
    } else {
        rec->fields[index] = NULL;
    }

    return 0;
}

/*---------------------------------------------*/

const char *record_get_field(const Record *rec, int index)
{
    if (!rec) {
        error_set("record_get_field: null record pointer");
        return NULL;
    }

    if (index < 0 || index >= NUM_FIELDS) {
        error_set("record_get_field: index out of range");
        return NULL;
    }

    return rec->fields[index];
}

/*---------------------------------------------*/

void record_destroy(Record *rec)
{
    if (!rec)
        return;

    for (int i = 0; i < NUM_FIELDS; i++) {
        free(rec->fields[i]);
    }

    free(rec);
}
