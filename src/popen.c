/*
 * =====================================================================================
 *
 *       Filename:  popen.c
 *
 *    Description:  popen的模拟实现
 *
 *        Version:  1.0
 *        Created:  2018-04-16
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

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define READ 0
#define WRITE 1

FILE *open(const char *command, const char *mode) {
        int pfp[2], pid;
        FILE *fdopen(), *fp;
        int parent_end, child_end;

        if (*mode == 'r') {
                parent_end = READ;
                child_end = WRITE;
        } else if (*mode == 'w') {
                parent_end = WRITE;
                child_end = READ;
        } else
                return NULL;

        if (pipe(pfp) == -1) return NULL;

        if ((pid = fork()) == -1) {
                close(pfp[0]);
                close(pfp[1]);
                return NULL;
        }

        /* parent code */
        if (pid > 0) {
                if (close(pfp[child_end]) == -1) return NULL;
                return fdopen(pfp[parent_end], mode);
        }

        /* child code */
        if (close(pfp[parent_end]) == -1) exit(1);

        if (dup2(pfp[child_end], child_end) == -1) exit(1);

        if (close(pfp[child_end]) == -1) exit(1);

        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(1);
}
