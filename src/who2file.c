/*
 * =====================================================================================
 *
 *       Filename:  who2file.c
 *
 *    Description:  子进程重定向
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
        int pid;
        int fd;

        printf("about to run who into a file\n");

        /* create a new process */

        if ((pid = fork()) == -1) {
                perror("fork");
                exit(1);
        }

        /* child does the job */
        if (pid == 0) {
                close(1);
                fd = creat("userlist.txt", 0644);
                execlp("who", "who", NULL);
                perror("execlp");
                exit(1);
        }

        /* parents wait the reports */
        if (pid != 0) {
                wait(NULL);
                printf("Done running who. result in userlist.txt\n");
        }
        exit(0);
}
