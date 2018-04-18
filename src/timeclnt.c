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
}
