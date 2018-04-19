/*
 * =====================================================================================
 *
 *       Filename:  rls.c
 *
 *    Description:  remote ls客户端
 *
 *        Version:  1.0
 *        Created:  2018-04-19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define PORTNUM 15000
#define oops(msg)                                                              \
        {                                                                      \
                perror(msg);                                                   \
                exit(1);                                                       \
        }

int main(int ac, char **av) {
        struct sockaddr_in servadd;
        struct hostent *hp;
        int sock_id, sock_fd;
        char buffer[BUFSIZ];
        int n_read;

        if (ac != 3)
                exit(1);

        /* step 1: get a socket */
        sock_id = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_id == 0)
                oops("socket");

        /* step 2: connect to server */
        bzero(&servadd, sizeof(servadd));
        hp = gethostbyname(av[1]);
        if (hp == NULL)
                oops(av[1]);
        bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);
        servadd.sin_port = htons(PORTNUM);
        servadd.sin_family = AF_INET;

        if (connect(sock_id, (struct sockaddr *)&servadd, sizeof(servadd)) != 0)
                oops("connect");

        /* step 3: send directory name, then read back results */
        if (write(sock_id, av[2], strlen(av[2])) == -1)
                oops("write");
        if (write(sock_id, "\n", 1) == -1)
                oops("write");

        while ((n_read = read(sock_id, buffer, BUFSIZ)) > 0)
                if (write(1, buffer, n_read) == -1)
                        oops("write");
        close(sock_id);
}
