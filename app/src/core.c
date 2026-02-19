#include <stdio.h>
#include "core.h"
#include "db.h"
#include "table.h"
#include "error.h"

static Database *g_db = NULL;

int core_init(const char *path)
{
    if (g_db)
        return -1;

    g_db = db_create();
    if (!g_db)
        return -1;

    if (db_open(g_db, path) != 0) {
        fprintf(stderr, "%s\n", error_get());
        db_destroy(g_db);
        g_db = NULL;
        return -1;
    }

    return 0;
}

/*---------------------------------------------*/

void core_shutdown(void)
{
    if (!g_db)
        return;

    db_close(g_db);
    db_destroy(g_db);
    g_db = NULL;
}

/*---------------------------------------------*/

int core_create_table(const char *name)
{
    if (!g_db)
        return -1;

    if (db_create_table(g_db, name) != 0) {
        fprintf(stderr, "%s\n", error_get());
        return -1;
    }

    return 0;
}

/*---------------------------------------------*/

int core_drop_table(const char *name)
{
    if (!g_db)
        return -1;

    if (db_drop_table(g_db, name) != 0) {
        fprintf(stderr, "table not found\n");
        return -1;
    }

    return 0;
}

/*---------------------------------------------*/

void core_list_tables(void)
{
    if (!g_db)
        return;

    size_t count = db_table_count(g_db);

    for (size_t i = 0; i < count; i++) {
        Table *table = db_table_at(g_db, i);
        if (table)
            printf("%s\n", table_get_name(table));
    }
}
