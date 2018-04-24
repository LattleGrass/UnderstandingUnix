/*
 * =====================================================================================
 *
 *       Filename:  incrprint.c
 *
 *    Description:  线程共享内存例子
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

int counter = 0;

int main() {
        pthread_t t1;

        void *print_count(void *);
        int i;

        pthread_create(&t1, NULL, print_count, NULL);

        for (i = 0; i < NUM; i++) {
                counter += 1;
                sleep(1);
        }
        pthread_join(t1, NULL);
}

void *print_count(void *m) {
        int i;
        for (i = 0; i < NUM; i++) {
                printf("count = %d\n", counter);
                sleep(2);
        }
        return NULL;
}
