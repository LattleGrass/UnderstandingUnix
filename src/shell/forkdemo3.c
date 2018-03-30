/*
 * =====================================================================================
 *
 *       Filename:  forkdemo3.c
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
        int fork_rv;

        printf("Before: my pid is %d\n", getpid());

        fork_rv = fork();
        if (fork_rv == -1)
                perror("fork");
        else if (fork_rv == 0)
                printf("I am child, my pid is %d\n", getpid());
        else
                printf("I am the parent, my child is %d\n", fork_rv);
        return 1;
}
