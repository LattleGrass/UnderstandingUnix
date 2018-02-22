/*
 * =====================================================================================
 *
 *       Filename:  sigdemo1.c
 *
 *    Description:  捕捉signal
 *
 *        Version:  1.0
 *        Created:  2018-02-22
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

int main() {
        void f(int);
        int i;
        signal(SIGINT, f);

        for (i = 0; i < 5; ++i) {
                printf("hello\n");
                sleep(1);
        }
        return 1;
}

void f(int signum) { printf("OUCH! \n"); }
