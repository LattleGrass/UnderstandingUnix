/*
 * =====================================================================================
 *
 *       Filename:  webserv.c
 *
 *    Description:  web服务器demo
 *
 *        Version:  1.0
 *        Created:  2018-04-23
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
#include <sys/stat.h>
#include <sys/types.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main(int ac, char *av[]) {
        int sock, fd;
        FILE *fpin;
        char request[BUFSIZ];
        if (ac == 1) {
                fprintf(stderr, "usage: ws portnum\n");
                exit(1);
        }
        sock = make_server_socket(atoi(av[1]));
        if (sock == -1)
                exit(2);

        while (1) {
                /* take a call and buffer it */
                fd = accept(sock, NULL, NULL);
                fpin = fdopen(fd, "r");

                /* read request */
                fgets(request, BUFSIZ, fpin);
                printf("got a call: request=%s", request);
                read_til_crnl(fpin);

                /* do what client asks */
                process_rq(request, fd);
                fclose(fpin);
        }
}

void read_til_crnl(FILE *fp) {
        char buf[BUFSIZ];
        while (fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf, "\r\n" != 0))
                ;
}

void process_rq(char *rq, int fd) {
        char cmd[BUFSIZ], arg[BUFSIZ];

        /* create a new process and return if not the child */
        if (fork() != 0)
                return;
        strcpy(arg, "/");
        if (sscanf(rq, "%s%s", cmd, arg + 2) != 2)
                return;
        if (strcmp(cmd, "GET") != 0)
                cannot_do(fd);
        else if (not_exist(arg))
                do_404(arg, fd);
        else if (isadir(arg))
                do_ls(arg, fd);
        else if (ends_in_cgi(arg))
                do_exec(arg, fd);
        else
                do_cat(arg, fd);
}
