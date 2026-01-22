#ifndef GAME_H
#define GAME_H

struct Table;
struct Record;

int table_open(struct Table *table, const char *name);
int table_close(struct Table *table);

int table_insert(struct Table *table, const struct Record *rec);
int table_read(struct Table *table, int index, struct Record *out);

int table_count(const struct Table *table);

#endif