/*
 * =====================================================================================
 *
 *       Filename:  sigdemo2.c
 *
 *    Description:  忽略信号的例子
 *
 *        Version:  1.0
 *        Created:  2018-02-23
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
        signal(SIGINT, SIG_IGN);
        printf("you cannot stop me!\n");
        while (1) {
                sleep(1);
                printf("haha\n");
        }
        return 1;
}
