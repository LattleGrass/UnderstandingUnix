/*
 * =====================================================================================
 *
 *       Filename:  execute.c
 *
 *    Description:  code used by small shell
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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int execute(char *argv[]) {
        int pid;
        int child_info = -1;

        if (argv[0] == NULL) return 0;

        if ((pid = fork()) == -1)
                perror("fork");
        else if (pid == 0) {
                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                execvp(argv[0], argv);
                perror("cannot execute command");
                exit(1);
        } else {
                if (wait(&child_info) == -1) perror("wait");
        }
        return child_info;
}
