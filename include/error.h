#ifndef ERROR_H
#define ERROR_H

char *string_dup(const char *s);
void error_set(const char *msg);
const char *error_get(void);
void error_clear(void);


#endif