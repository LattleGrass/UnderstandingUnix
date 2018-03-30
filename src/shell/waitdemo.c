/*
 * =====================================================================================
 *
 *       Filename:  waitdemo.c
 *
 *    Description:  wait功能使用
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
#define DELAY 2

int main() {
        int newpid;
        void child_code(), parent_code();

        printf("before: my pid is %d\n", getpid());

        if ((newpid = fork()) == -1)
                perror("fork");
        else if (newpid == 0)
                child_code(DELAY);
        else
                parent_code(newpid);
        return 0;
}

void child_code(int delay) {
        printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
        sleep(delay);
        printf("child done! about to exit\n");
        exit(17);
}

void parent_code(int childpid) {
        int wait_rv;
        wait_rv = wait(NULL);
        printf("done waiting for %d. Wait returned: %d\n", childpid, wait_rv);
}
