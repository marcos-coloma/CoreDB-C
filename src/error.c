#include <stdlib.h>
#include <string.h>
#include "error.h"

static char *current_error = NULL;

/*---------------------------------------------*/

char *string_dup(const char *s)
{
    if (!s) return NULL;

    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (!copy) return NULL;

    memcpy(copy, s, len);
    return copy;
}


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

/*---------------------------------------------*/

const char *error_get(void)
{
    return current_error;
}

/*---------------------------------------------*/

void error_set(const char *msg)
{
    error_free_current();
    current_error = string_dup(msg);
}
