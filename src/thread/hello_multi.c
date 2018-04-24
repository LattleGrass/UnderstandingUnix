/*
 * =====================================================================================
 *
 *       Filename:  hello_multi.c
 *
 *    Description:  多线程
 *
 *        Version:  1.0
 *        Created:  2018-04-24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define NUM 5

int main() {
        pthread_t t1, t2;

        void *print_msg(void *);

        pthread_create(&t1, NULL, print_msg, (void *)"hello");
        pthread_create(&t2, NULL, print_msg, (void *)" world\n");

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
}

void *print_msg(void *m) {
        char *cp = (char *)m;
        int i;
        for (i = 0; i < NUM; i++) {
                printf("%s", m);
                fflush(stdout);
                sleep(1);
        }
        return NULL;
}
