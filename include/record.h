#ifndef RECORD_H
#define RECORD_H


#define MAX_FIELDS 10

struct Record {
    char *fields[MAX_FIELDS];
};

int record_init(struct Record *rec);
int record_set_field(struct Record *rec, int index, const char *value);
const char *record_get_field(const struct Record *rec, int index);
void record_free(struct Record *rec);



#endif