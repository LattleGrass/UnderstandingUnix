#include "varlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smsh.h"

static struct var *VLBuf[BUFSIZ];
static int VLindex = 0;

int VLstore(char *name, char *val) {
        if (VLindex >= BUFSIZ) {
                return 0;
        }
        struct var *tmp;
        char *tn, *tv;
        tn = emalloc((strlen(name) + 1) * sizeof(char));
        tv = emalloc((strlen(val) + 1) * sizeof(char));
        tn = strcpy(tn, name);
        tv = strcpy(tv, val);
        if ((tmp = VLfind(tn)) == NULL) {
                tmp = emalloc(sizeof(struct var));
                tmp->name = tn;
                tmp->val = tv;
                tmp->global = 0;
                VLBuf[VLindex] = tmp;
                VLindex++;
        } else {
                tmp->val = tv;
        }
        return 0;
}

int VLexport(char *name) {
        struct var *tmp;
        if ((tmp = VLfind(name)) == NULL) {
                return 0;
        } else {
                tmp->global = 1;
                return 1;
        }
}

void VLlist() {
        int i;
        for (i = 0; i < VLindex; i++) {
                printf("%s=%s\n", VLBuf[i]->name, VLBuf[i]->val);
        }
}

struct var *VLfind(char *name) {
        int i;
        for (i = 0; i < VLindex; i++) {
                if (strcmp(VLBuf[i]->name, name) == 0) {
                        return VLBuf[i];
                }
        }
        return NULL;
}

void VLfree() {
        int i;
        for (i = 0; i < VLindex; i++) {
                free(VLBuf[i]->name);
                free(VLBuf[i]->val);
                free(VLBuf[i]);
        }
        VLindex = 0;
}
