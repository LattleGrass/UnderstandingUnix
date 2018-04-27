/*
 * =====================================================================================
 *
 *       Filename:  selectdemo.c
 *
 *    Description:  进程挂起
 *
 *        Version:  1.0
 *        Created:  2018-04-27
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
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define oops(m, x)                                                             \
        {                                                                      \
                perror(m);                                                     \
                exit(x);                                                       \
        }

int main(int ac, char **av) {
        int fd1, fd2;
        struct timeval timeout;
        fd_set readfds;
        int maxfd;
        int retval;
        void showdata(char *, int);

        if (ac != 4) {
                fprintf(stderr, "usage: %s file file timeout", *av);
                exit(1);
        }

        /* open files */

        if ((fd1 = open(av[1], O_RDONLY)) == -1)
                oops(av[1], 2);
        if ((fd2 = open(av[2], O_RDONLY)) == -1)
                oops(av[2], 3);
        maxfd = 1 + (fd1 > fd2 ? fd1 : fd2);

        while (1) {
                /* make a list of file discriptor to watch */
                FD_ZERO(&readfds);
                FD_SET(fd1, &readfds);
                FD_SET(fd2, &readfds);

                /* set timeout */
                timeout.tv_sec = atoi(av[3]);
                timeout.tv_usec = 0;

                /* wait for input */
                retval = select(maxfd, &readfds, NULL, NULL, &timeout);
                if (retval == -1)
                        oops("select", 4);
                if (retval > 0) {
                        /* check bits for each fd */
                        if (FD_ISSET(fd1, &readfds))
                                showdata(av[1], fd1);
                        if (FD_ISSET(fd2, &readfds))
                                showdata(av[2], fd2);
                } else {
                        printf("no input after %d seconds\n", atoi(av[3]));
                }
        }
}

void showdata(char *fname, int fd) {
        char buf[BUFSIZ];
        int n;

        printf("%s: ", fname);
        fflush(stdout);
        n = read(fd, buf, BUFSIZ);
        if (n == -1)
                oops(fname, 5);
        write(1, buf, n);
        write(1, "\n", 1);
}
