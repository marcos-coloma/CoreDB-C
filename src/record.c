#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "error.h" 

int record_init(struct Record *rec) {
    if (!rec) {
        error_set("record_init: null record pointer");
        return -1;
    }

    for (int i = 0; i < MAX_FIELDS; i++) {
        rec->fields[i] = NULL;
    }

    return 0;
}

int record_set_field(struct Record *rec, int index, const char *value) {
    if (!rec) {
        error_set("record_set_field: null record pointer");
        return -1;
    }

    if (index < 0 || index >= MAX_FIELDS) {
        error_set("record_set_field: index out of range");
        return -1;
    }

    if (rec->fields[index]) {
        free(rec->fields[index]);
    }


    if (value) {
        rec->fields[index] = strdup(value);
        if (!rec->fields[index]) {
            error_set("record_set_field: memory error");
            return -1;
        }
    } else {
        rec->fields[index] = NULL;
    }

    return 0;
}
