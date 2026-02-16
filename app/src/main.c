#include "cli.h"
#include "core.h"

int main(void) {
    core_init();
    cli_start();
    core_shutdown();
    return 0;
}
