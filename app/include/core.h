#ifndef CORE_H
#define CORE_H

int  core_init(const char *path);
void core_shutdown(void);

int  core_create_table(const char *name);
int  core_drop_table(const char *name);
void core_list_tables(void);

#endif
