/*
 * =====================================================================================
 *
 *       Filename:  socketlib.c
 *
 *    Description:  web服务端工具包
 *
 *        Version:  1.0
 *        Created:  2018-04-20
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
#include <time.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define HOSTLEN 256
#define BACKLOG 1

int make_server_socket_q(int, int);
int make_server_socket(int portnum) {
        return make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int portnum, int backlog) {
        struct sockaddr_in saddr;
        struct hostent *hp;
        char hostname[HOSTLEN];
        int sock_id;

        sock_id = socket(PF_INET, SOCK_STREAM, 0);
        if (sock_id == -1)
                return -1;

        /* build address and bind it to socket */
        bzero((void *)&saddr, sizeof(saddr));
        gethostname(hostname, HOSTLEN);
        printf("%s\n", hostname);
        hp = gethostbyname(hostname);

        bcopy((void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
        saddr.sin_port = htons(portnum);
        saddr.sin_family = AF_INET;

        if (bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
                return -1;

        /* arrange for incoming calls */
        if (listen(sock_id, backlog) != 0)
                return -1;
        return sock_id;
}

int connect_to_server(char *host, int portnum) {
        int sock;
        struct sockaddr_in servadd;
        struct hostent *hp;

        /* step 1: get a socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
                return -1;

        /* step 2: connect to server */
        bzero(&servadd, sizeof(servadd));
        hp = gethostbyname(host);
        if (hp == NULL)
                return -1;
        bcopy((void *)hp->h_addr, (void *)&servadd.sin_addr, hp->h_length);
        servadd.sin_port = htons(portnum);
        servadd.sin_family = AF_INET;

        if (connect(sock, (struct sockaddr *)&servadd, sizeof(servadd)) != 0)
                return -1;
        return sock;
}
