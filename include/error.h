#ifndef ERROR_H
#define ERROR_H


void error_set(const char *msg);
const char *error_get(void);
void error_clear(void);


#endif