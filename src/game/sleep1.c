/*
 * =====================================================================================
 *
 *       Filename:  sleep1.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018-03-01
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

void wakeup(int);
int main() {
        printf("about to sleep 4 secs\n");
        signal(SIGALRM, wakeup);
        alarm(4);
        pause();
        printf("Morning so soon?\n");
}

void wakeup(int signum) { printf("Alarm received from kenerl\n"); }
