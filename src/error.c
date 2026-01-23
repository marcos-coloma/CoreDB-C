#include <stdlib.h>
#include <string.h>
#include "error.h"

static char *current_error = NULL;

/*---------------------------------------------*/

static void error_free_current(void)
{
    if (current_error) {
        free(current_error);
        current_error = NULL;
    }
}

/*---------------------------------------------*/

void error_clear(void)
{
    error_free_current();
}

const char *error_get(void)
{
    return current_error;
}

void error_set(const char *message)
{
    if (!message) {
        return;
    }

    error_free_current();
    current_error = strdup(message);
}




