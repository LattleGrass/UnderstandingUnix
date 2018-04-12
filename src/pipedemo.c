/*
 * =====================================================================================
 *
 *       Filename:  pipedemo.c
 *
 *    Description:  管道demo
 *
 *        Version:  1.0
 *        Created:  2018-04-12
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

int main() {
        int len, i, apipe[2];
        char buf[BUFSIZ];

        /* get a pipe */

        if (pipe(apipe) == -1) {
                perror("could not make a pipe");
                exit(1);
        }
        printf("Got a pipe! It is file descriptors: {%d %d}\n", apipe[0],
               apipe[1]);

        /* read from stdin, write into pipe, read from pipe, print */

        while (fgets(buf, BUFSIZ, stdin)) {
                len = strlen(buf);
                if (write(apipe[1], buf, len) != len) {
                        perror("writing to a pipe");
                        break;
                }
                for (i = 0; i < len; i++) buf[i] = 'X';
                len = read(apipe[0], buf, BUFSIZ);
                if (len == -1) {
                        perror("reading from pipe");
                        break;
                }
                if (write(1, buf, len) != len) {
                        perror("writing to stdout");
                        break;
                }
        }
        exit(0);
}
