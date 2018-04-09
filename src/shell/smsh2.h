#ifndef _SMSH_H_
#define _SMSH_H_

#define YES 1
#define NO 0

#include <stddef.h>

int process(char **);
char *next_cmd();
char **splitline(char *);
void freelist(char **);
void *emalloc(size_t);
void *erealloc(void *, size_t);
int execute(char **);
void fatal(char *, char *, int);

#endif
