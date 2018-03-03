/*
 * =====================================================================================
 *
 *       Filename:  ticker_demo.c
 *
 *    Description:  时钟练习
 *
 *        Version:  1.0
 *        Created:  2018-03-03
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
#include <sys/time.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void countdown(int signum);
int set_ticker(int n_msecs);

int main() {
        void countdown(int);
        signal(SIGALRM, countdown);
        if (set_ticker(1000) == -1)
                perror("set ticker");
        else
                while (1) pause();
        return 0;
}

void countdown(int signum) {
        static int num = 10;
        printf("%d..", num--);
        fflush(stdout);
        if (num < 0) {
                printf("DONE \n");
                exit(0);
        }
}

int set_ticker(int n_msecs) {
        struct itimerval new_timeset;
        long n_sec, n_usecs;

        n_sec = n_msecs / 1000;
        n_usecs = (n_msecs % 1000) * 1000L;
        new_timeset.it_interval.tv_sec = n_sec;
        new_timeset.it_interval.tv_usec = n_usecs;

        new_timeset.it_value.tv_sec = n_sec;
        new_timeset.it_value.tv_usec = n_usecs;
        return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
