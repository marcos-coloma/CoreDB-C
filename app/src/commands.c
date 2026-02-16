#include <stdio.h>
#include <string.h>
#include "commands.h"


static void handle_table_command(char *args)
{
    char *action = strtok(args, " ");
    if (!action) {
        printf("table: missing action\n");
        return;
    }

    if (strcmp(action, "list") == 0) {
        printf("Simulating: listing tables...\n");
        // core_list_tables();
    }

    else if (strcmp(action, "create") == 0) {

        char *name = strtok(NULL, " ");

        if (!name) {
            printf("table create: missing table name\n");
            return;
        }

        printf("Simulating: Create table '%s'...\n", name);
        // core_create_table(name);
    }

    else if (strcmp(action, "drop") == 0) {

        char *name = strtok(NULL, " ");

        if (!name) {
            printf("table drop: missing table name\n");
            return;
        }

        printf("simulating: deleting table '%s'...\n", name);
        // core_drop_table(name);
    }
    
    else {
        printf("unknown table action: %s\n", action);
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
        return;
    }

    if (strcmp(token1, "table") == 0) {
        char *args = strtok(NULL, "");
        handle_table_command(args);
        return;
    }

    printf("unknown command: %s\n", token1);
}
