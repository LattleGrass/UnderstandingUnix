/*
 * =====================================================================================
 *
 *       Filename:  timeserv.c
 *
 *    Description:  时间服务器
 *
 *        Version:  1.0
 *        Created:  2018-04-17
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
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg)                                                              \
        {                                                                      \
                perror(msg);                                                   \
                exit(1);                                                       \
        }

int main(int ac, char *av[]) {
        struct sockaddr_in saddr;
        struct hostent *hp;
        char hostname[HOSTLEN];
        int sock_id, sock_fd;
        FILE *sock_fp;
        char *ctime();
        time_t thetime;

        /* step1: ask kernel for a socket */

        /* 定义函数：int socket(int domain, int type, int protocol); */

        /* 函数说明：socket()用来建立一个新的socket, 也就是向系统注册,
         * 通知系统建立一通信端口. 参数domain 指定使用何种的地址类型,
         * 完整的定义在/usr/include/bits/socket.h 内, 底下是常见的协议: */
        /*    PF_UNIX/PF_LOCAL/AF_UNIX/AF_LOCAL UNIX 进程通信协议 */
        /*    PF_INET?AF_INET Ipv4 网络协议 */
        /*    PF_INET6/AF_INET6 Ipv6 网络协议 */
        /*    PF_IPX/AF_IPX IPX-Novell 协议 */
        /*    PF_NETLINK/AF_NETLINK 核心用户接口装置 */
        /*    PF_X25/AF_X25 ITU-T X. 25/ISO-8208 协议 */
        /*    PF_AX25/AF_AX25 业余无线AX. 25 协议 */
        /*    PF_ATMPVC/AF_ATMPVC 存取原始 ATM PVCs */
        /*    PF_APPLETALK/AF_APPLETALK appletalk (DDP)协议 */
        /*    PF_PACKET/AF_PACKET 初级封包接口 */

        /* 参数 type 有下列几种数值: */
        /* 1、SOCK_STREAM 提供双向连续且可信赖的数据流, 即TCP. 支持 OOB 机制,
         * 在所有数据传送前必须使用connect()来建立连线状态. */
        /* 2、SOCK_DGRAM 使用不连续不可信赖的数据包连接 */
        /* 3、SOCK_SEQPACKET 提供连续可信赖的数据包连接 */
        /* 4、SOCK_RAW 提供原始网络协议存取 */
        /* 5、SOCK_RDM 提供可信赖的数据包连接 */
        /* 6、SOCK_PACKET 提供和网络驱动程序直接通信. protocol 用来指定socket
         * 所使用的传输协议编号, 通常此参考不用管它, 设为0 即可. */
        sock_id = socket(PF_INET, SOCK_STREAM, 0);
        if (sock_id == -1)
                oops("socket");

        /* step2: bind address to socket. Address is host, port */
        /* bzero() 会将内存块（字符串）的前n个字节清零 */
        bzero((void *)&saddr, sizeof(saddr));

        /* int gethostname(char *name, size_t len); */
        /* 参数说明： */
        /* 这个函数需要两个参数： */
        /* 接收缓冲区name，其长度必须为len字节或是更长,存获得的主机名。*/
        /* 接收缓冲区name的最大长度 */
        gethostname(hostname, HOSTLEN);
        printf("%s\n", hostname);
        hp = gethostbyname(hostname);
        if (hp == NULL)
                oops("get host by name");
        printf("%s\n", hp->h_name);

        /* bcopy() 函数用来复制内存(字符串) */
        bcopy((void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
        /* htons()用来将参数指定的16 位hostshort 转换成网络字符顺序. */
        saddr.sin_port = htons(PORTNUM);
        saddr.sin_family = AF_INET;

        /* bind()用来设置给参数sockfd 的socket 一个名称. 此名称由参数my_addr
         * 指向一sockaddr 结构,对于不同的socket domain 定义了一个通用的数据结构
         */
        /* struct sockaddr */
        /* { */
        /*    unsigned short int sa_family; */
        /*    char sa_data[14]; */
        /* }; */
        /* 1、sa_family 为调用socket()时的domain 参数, 即AF_xxxx 值. */
        /* 2、sa_data 最多使用14 个字符长度. */
        if (bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
                oops("bind");

        /* steps: allow incoming calls with Qsize = 1 on socket */

        /* listen()用来等待参数s 的socket 连线. 参数backlog
         * 指定同时能处理的最大连接要求, 如果连接数目达此上限则client
         * 端将收到ECONNREFUSED 的错误. Listen()并未开始接收连线, 只是设置socket
         * 为listen 模式, 真正接收client 端连线的是accept().
         * 通常listen()会在socket(), bind()之后调用, 接着才调用accept(). */
        if (listen(sock_id, 1) != 0)
                oops("listen");

        while (1) {
                /* accept()用来接受参数s 的socket 连线. 参数s 的socket
                 * 必需先经bind()、listen()函数处理过,
                 * 当有连线进来时accept()会返回一个新的socket 处理代码,
                 * 往后的数据传送与读取就是经由新的socket处理, 而原来参数s
                 * 的socket 能继续使用accept()来接受新的连线要求. 连线成功时,
                 * 参数addr 所指的结构会被系统填入远程主机的地址数据,
                 * 参数addrlen 为scokaddr 的结构长度. 关于机构sockaddr
                 * 的定义请参考bind(). */
                printf("hahaha\n");
                sock_fd = accept(sock_id, NULL, NULL);
                printf("Wow! got a call!\n");
                if (sock_fd == -1)
                        oops("accept");
                sock_fp = fdopen(sock_fd, "w");
                if (sock_fp == NULL)
                        oops("fdopen");

                thetime = time(NULL);
                fprintf(sock_fp, "The time here is...");
                fprintf(sock_fp, "%s", ctime(&thetime));
                fclose(sock_fp);
        }
        exit(0);
}
