/*
 * =====================================================================================
 *
 *       Filename:  stdinredir2.c
 *
 *    Description:  重定向demo2
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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

/* #define CLOSE_DUP */
/* #define USE_DUP2 */

int main() {
        int fd, newfd;
        char line[100];

        /* read and print three lines  */
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);

        /* redirect input */
        fd = open("data", O_RDONLY);
#ifdef CLOSE_DUP
        close(0);
        newfd = dup(fd);
#else
        newfd = dup2(fd, 0);
#endif
        if (newfd != 0) {
                fprintf(stderr, "Could not duplicate fd to 0\n");
                exit(1);
        }
        close(fd);
        /* read and print three lines  */
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);

        exit(0);
}
