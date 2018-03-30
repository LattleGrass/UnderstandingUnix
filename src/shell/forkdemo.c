/*
 * =====================================================================================
 *
 *       Filename:  forkdemo.c
 *
 *    Description:  fork简单接触
 *
 *        Version:  1.0
 *        Created:  2018-03-30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main() {
        int ret_from_fork, mypid;

        mypid = getpid();
        printf("Before: my pid is %d\n", mypid);
        ret_from_fork = fork();
        sleep(1);
        printf("After: my pid is %d, fork() said %d\n", getpid(),
               ret_from_fork);
        return 1;
}
