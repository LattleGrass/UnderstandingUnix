/*
 * =====================================================================================
 *
 *       Filename:  stdinredir1.c
 *
 *    Description:  重定向demo
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

int main() {
        int fd;
        char line[100];

        /* read and print three lines  */
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);

        /* redirect input */
        close(0);
        fd = open("/etc/passwd", O_RDONLY);
        if (fd != 0) {
                fprintf(stderr, "Could not open data as fd 0 \n");
                exit(1);
        }

        /* read and print three lines  */
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);
        fgets(line, 100, stdin);
        printf("%s", line);
        exit(0);
}
