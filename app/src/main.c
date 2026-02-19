#include <stdio.h>
#include "cli.h"
#include "core.h"

int main(int argc, char **argv)
{
    const char *path = "./data";

    if (argc > 1)
        path = argv[1];

    if (core_init(path) != 0) {
        fprintf(stderr, "Failed to initialize database\n");
        return 1;
    }

    cli_start();

    core_shutdown();
    return 0;
}
