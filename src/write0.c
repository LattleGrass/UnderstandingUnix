/*
 * =====================================================================================
 *
 *       Filename:  write0.c
 *
 *    Description:  write简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-29
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
#include <string.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main(int ac, char *av[]) {
        int fd;
        char buf[BUFSIZ];

        /* check args */
        if (ac != 2) {
                fprintf(stderr, "usage: write0 ttyname\n");
                exit(1);
        }

        /* open devices */
        fd = open(av[1], O_WRONLY);
        if (fd == -1) {
                perror(av[1]);
                exit(1);
        }

        /* loop util EOF on input */
        while (fgets(buf, BUFSIZ, stdin) != NULL)
                if (write(fd, buf, strlen(buf)) == -1) break;
        close(fd);
        return 1;
}
