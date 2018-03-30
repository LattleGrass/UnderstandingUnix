/*
 * =====================================================================================
 *
 *       Filename:  forkdemo2.c
 *
 *    Description:
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
        printf("my pid is %d\n", getpid());
        fork();
        fork();
        fork();
        printf("my pid is %d\n", getpid());
        return 1;
}
