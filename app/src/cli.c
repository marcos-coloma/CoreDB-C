#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "cli.h"

void cli_start(void)
{
    char input[INPUT_SIZE];

    while (1)
    {
        printf("> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        if (strcmp(input, "exit") == 0)
            break;

        commands_execute(input);
    }
}
