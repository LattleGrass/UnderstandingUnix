#ifndef _VARLIB_H
#define _VARLIB_H
/* varlib.h
 */
#include <stdio.h>

struct var {
        char *str;
        int global;
};

void VLlist();
int VLexport(char *);
int VLstore(char *, char *);
struct var *VLfind(char *);
void VLfree();
void VLenviron2table(char **);
char **VLtable2environ(void);
#endif
