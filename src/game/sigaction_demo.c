/*
 * =====================================================================================
 *
 *       Filename:  sigaction_demo.c
 *
 *    Description:  sigaction例子
 *
 *        Version:  1.0
 *        Created:  2018-03-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define INPUTLEN 100

int main() {
        struct sigaction newhandler;
        sigset_t blocked;
        void inthandler();
        char x[INPUTLEN];

        newhandler.sa_handler = inthandler;
        newhandler.sa_flags = SA_RESTART;

        sigemptyset(&blocked);
        sigaddset(&blocked, SIGQUIT);
        newhandler.sa_mask = blocked;

        if (sigaction(SIGINT, &newhandler, NULL) == -1)
                perror("sigaction");
        else
                while (1) {
                        fgets(x, INPUTLEN, stdin);
                        printf("input: %s", x);
                }
        return 1;
}

void inthandler(int s) {
        printf("Called with signal %d\n", s);
        sleep(s);
        printf("done dealing with signal %d\n", s);
}
