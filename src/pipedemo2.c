/*
 * =====================================================================================
 *
 *       Filename:  pipedemo2.c
 *
 *    Description:  pipe与fork协作
 *
 *        Version:  1.0
 *        Created:  2018-04-13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS "testing...\n"
#define oops(m, x)         \
        {                  \
                perror(m); \
                exit(x);   \
        }

int main() {
        int pipefd[2];
        int len;
        char buf[BUFSIZ];
        int read_len;

        if (pipe(pipefd) == -1) oops("cannot get a pipe", 1);

        switch (fork()) {
                case -1:
                        oops("cannot fork", 2);
                case 0:
                        len = strlen(CHILD_MESS);
                        while (1) {
                                if (write(pipefd[1], CHILD_MESS, len) != len)
                                        oops("write", 3);
                                sleep(5);
                        }
                default:
                        len = strlen(PAR_MESS);
                        while (1) {
                                if (write(pipefd[1], PAR_MESS, len) != len)
                                        oops("write", 4);
                                sleep(1);
                                read_len = read(pipefd[0], buf, BUFSIZ);
                                if (read_len <= 0) break;
                                write(1, buf, read_len);
                        }
        }
        exit(0);
}
