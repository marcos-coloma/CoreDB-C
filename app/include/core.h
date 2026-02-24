#ifndef CORE_H
#define CORE_H

int  core_init(const char *path);
void core_shutdown(void);

int  core_create_table(const char *name);
int  core_drop_table(const char *name);
void core_list_tables(void);

int  core_use_table(const char *name);

int  core_insert_record(char **fields, int field_count);
int  core_read_record(int index);
int  core_update_record(int index, char **fields, int field_count);
int  core_delete_record(int index);
void core_list_records(void);

#endif
