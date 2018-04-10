/*
 * =====================================================================================
 *
 *       Filename:  smsh2.c
 *
 *    Description:  small shell
 *
 *        Version:  1.0
 *        Created:  2018-04-04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "smsh2.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define DFL_PROMPT "> "

int main() {
        char *cmdline, *prompt, **arglist;

        int result;
        void setup();

        prompt = DFL_PROMPT;
        setup();

        while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
                if ((arglist = splitline(cmdline)) != NULL) {
                        result = process(arglist);
                        freelist(arglist);
                }
                free(cmdline);
        }
        return 0;
}

void setup() {
        extern char **environ;
        VLenviron2table(environ);
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n) {
        fprintf(stderr, "Error: %s, %s\n", s1, s2);
        exit(n);
}
