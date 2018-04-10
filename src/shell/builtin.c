/*
 * =====================================================================================
 *
 *       Filename:  builtin.c
 *
 *    Description:  判断是不是内置命令
 *
 *        Version:  1.0
 *        Created:  2018-04-09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smsh2.h"
#include "varlib.h"

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int assign(char *);
int okname(char *);

int builtin_command(char **args, int *resultp) {
        /* run built in command */
        int rv = 0;
        if (strcmp(args[0], "set") == 0) {
                VLlist();
                *resultp = 0;
                rv = 1;
        } else if (strchr(args[0], '=') != NULL) {
                *resultp = assign(args[0]);
                if (*resultp != -1) rv = 1;
        } else if (strcmp(args[0], "export") == 0) {
                if (args[1] != NULL && okname(args[1]))
                        *resultp = VLexport(args[1]);
                else
                        *resultp = 1;
                rv = 1;
        }
        return rv;
}

int assign(char *str) {
        char *cp;
        int rv;
        cp = strchr(str, '=');
        *cp = '\0';
        rv = (okname(str) ? VLstore(str, cp + 1) : -1);
        *cp = '=';
        return rv;
}

int okname(char *str) {
        char *cp;
        for (cp = str; *cp; cp ++) {
                if ((isdigit(*cp) && cp == str) ||
                    !(isalnum(*cp) || *cp == '_'))
                        return 0;
        }
        return (cp != str);
}
