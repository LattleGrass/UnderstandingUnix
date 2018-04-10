/*
 * =====================================================================================
 *
 *       Filename:  process.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018-04-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "smsh2.h"

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int is_control_command(char *);
int do_control_command(char **);
int ok_to_execute();

int process(char **args) {
        int rv = 0;
        if (args[0] == NULL)
                rv = 0;
        else if (is_control_command(args[0]))
                rv = do_control_command(args);
        else if (ok_to_execute())
                if (!builtin_command(args, &rv)) rv = execute(args);
        return rv;
}
