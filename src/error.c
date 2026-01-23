#include <stdlib.h>
#include <string.h>
#include "error.h"

static char *current_error = NULL;

/*---------------------------------------------*/

static char *string_dup(const char *s) {
    if (!s) return NULL;

#ifdef _MSC_VER
    return _strdup(s);
#else
    return strdup(s);
#endif
}

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

void error_set(const char *msg) {
    if (current_error) {
        free(current_error);
    }
    current_error = string_dup(msg);
}



