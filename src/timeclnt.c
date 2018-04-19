/*
 * =====================================================================================
 *
 *       Filename:  timeclnt.c
 *
 *    Description:  时间服务客户端
 *
 *        Version:  1.0
 *        Created:  2018-04-18
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
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define oops(msg)                                                              \
        {                                                                      \
                perror(msg);                                                   \
                exit(1);                                                       \
        }

int main(int ac, char **av) {
        struct sockaddr_in servadd;
        struct hostent *hp;
        int sock_id, sock_fd;
        char message[BUFSIZ];
        int messlen;

        /* step 1: Get a socket */
        sock_id = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_id == -1)
                oops("socket");

        /* step 2: connect to a server */
        bzero(&servadd, sizeof(servadd));

        hp = gethostbyname(av[1]);
        if (hp == NULL)
                oops(av[1]);
        bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);

        servadd.sin_port = htons(atoi(av[2]));
        servadd.sin_family = AF_INET;

        if (connect(sock_id, (struct sockaddr *)&servadd, sizeof(servadd)) != 0)
                oops("connect");

        /* step3: transfer data from server, then hangup */
        messlen = read(sock_id, message, BUFSIZ);
        if (messlen == -1)
                oops("read");
        if (write(1, message, messlen) != messlen)
                oops("write");
        close(sock_id);
        exit(0);
}
