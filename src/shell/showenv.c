/*
 * =====================================================================================
 *
 *       Filename:  showenv.c
 *
 *    Description:  显示环境变量
 *
 *        Version:  1.0
 *        Created:  2018-04-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

extern char **environ;

int main() {
        int i;
        for (i = 0; environ[i]; i++) {
                printf("%s\n", environ[i]);
        }
        exit(0);
}
