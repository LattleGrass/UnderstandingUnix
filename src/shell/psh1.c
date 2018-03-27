/*
 * =====================================================================================
 *
 *       Filename:  psh1.c
 *
 *    Description:  promoting shell
 *
 *        Version:  1.0
 *        Created:  2018-03-27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MAXARGS 20
#define ARGLEN 100

int main() {
        char *arglist[MAXARGS + 1];
        int numargs;
        char argbuf[ARGLEN];
        char *makestring();
        numargs = 0;
        while (numargs < MAXARGS) {
                printf("Arg[%d]?", numargs);
                if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
                        arglist[numargs++] = makestring(argbuf);
                else {
                        if (numargs > 0) {
                                arglist[numargs] = NULL;
                                execute(arglist);
                                numargs = 0;
                        }
                }
        }
        return 0;
}

int execute(char *arglist[]) {
        execvp(arglist[0], arglist);
        perror("execvp failed");
        exit(1);
}

char *makestring(char *buf) {
        char *cp, *malloc();
        buf[strlen(buf) - 1] = '\0';
        cp = malloc(strlen(buf) + 1);
        if (cp == NULL) {
                fprintf(stderr, "no memory\n");
                exit(1);
        }
        strcpy(cp, buf);
        return cp;
}
