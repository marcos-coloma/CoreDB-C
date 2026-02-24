#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "core.h"
#include "schema.h"

static void handle_table_command(char *args)
{
    char *action = strtok(args, " ");
    if (!action) {
        printf("table: missing action\n");
        return;
    }

    if (strcmp(action, "list") == 0) {
        printf("listing tables\n");
        core_list_tables();
    }

    else if (strcmp(action, "create") == 0) {

        char *name = strtok(NULL, " ");

        if (!name) {
            printf("table create: missing table name\n");
            return;
        }

        printf("Create table '%s'\n", name);
        core_create_table(name);
    }

    else if (strcmp(action, "drop") == 0) {

        char *name = strtok(NULL, " ");

        if (!name) {
            printf("table drop: missing table name\n");
            return;
        }

        printf("drop table '%s'\n", name);
        core_drop_table(name);
    }

    else if (strcmp(action, "use") == 0) {
        char *name = strtok(NULL, " ");

        if (!name) {
            printf("table use: missing table name\n");
            return;
        }

        core_use_table(name);
    }
    
    else {
        printf("unknown table action: %s\n", action);
    }
}

static void handle_record_command(char *args)
{
    char *action = strtok(args, " ");
    if (!action) {
        printf("record: missing action\n");
        return;
    }

    if (strcmp(action, "insert") == 0) {

        char *fields[NUM_FIELDS];
        int count = 0;

        char *token;
        while ((token = strtok(NULL, " ")) != NULL && count < NUM_FIELDS) {
            fields[count++] = token;
        }

        core_insert_record(fields, count);
    }

    else if (strcmp(action, "read") == 0) {

        char *index_str = strtok(NULL, " ");
        if (!index_str) {
            printf("record read: missing index\n");
            return;
        }

        int index = atoi(index_str);
        core_read_record(index);
    }

    else if (strcmp(action, "delete") == 0) {

        char *index_str = strtok(NULL, " ");
        if (!index_str) {
            printf("record delete: missing index\n");
            return;
        }

        int index = atoi(index_str);
        core_delete_record(index);
    }

    else if (strcmp(action, "list") == 0) {

        core_list_records();
    }

    else {
        printf("unknown record action: %s\n", action);
    }
}

void commands_execute(const char *input)
{
    char buffer[256];
    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token1 = strtok(buffer, " ");
    if (!token1) return;

    if (strcmp(token1, "help") == 0) {
        printf("available commands:\n");
        printf("  table list\n");
        printf("  table create <name>\n");
        printf("  table drop <name>\n");
        printf("  table use <name>\n");
        printf("  record insert <f1> <f2> ...\n");
        printf("  record read <index>\n");
        printf("  record update <index> <f1> <f2> ...\n");
        printf("  record delete <index>\n");
        printf("  record list\n");
        printf("  exit\n");
        return;
    }

    if (strcmp(token1, "table") == 0) {
        char *args = strtok(NULL, "");
        if (!args) {
            printf("table: missing action\n");
            return;
        }
        handle_table_command(args);
        return;
    }

    if (strcmp(token1, "exit") == 0 ||
        strcmp(token1, "quit") == 0) {
        core_shutdown();
        exit(0);
    }

    if (strcmp(token1, "record") == 0) {
        char *args = strtok(NULL, "");
        if (!args) {
            printf("record: missing action\n");
            return;
        }
        handle_record_command(args);
        return;
    }

    printf("unknown command: %s\n", token1);
}
