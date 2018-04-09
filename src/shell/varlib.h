#ifndef _VARLIB_H
#define _VARLIB_H
/* varlib.h
 */
#include <stdio.h>

struct var {
        char *name;
        char *val;
        int global;
};

void VLlist();
int VLexport(char *);
int VLstore(char *, char *);
struct var *VLfind(char *);
void VLfree();
#endif
