/*
 * =====================================================================================
 *
 *       Filename:  signal_test.c
 *
 *    Description:  多信号测试
 *
 *        Version:  1.0
 *        Created:  2018-03-06
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
#include <string.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define INPUTLEN 100

int main(int ac, char *av[]) {
        void inthandler(int);
        void quithandler(int);
        char input[INPUTLEN];
        int nchars;

        signal(SIGINT, inthandler);
        signal(SIGQUIT, quithandler);

        do {
                printf("\n Type a message\n");
                nchars = read(0, input, (INPUTLEN - 1));
                if (nchars == -1)
                        perror("read returned an error");
                else {
                        input[nchars] = '\0';
                        printf("You typed: %s", input);
                }
        } while (strncmp(input, "quit", 4) != 0);
}

void inthandler(int s) {
        printf("Received signal %d.. waiting\n", s);
        sleep(2);
        printf("Leaving inthandler\n");
}

void quithandler(int s) {
        printf("Received signal %d..waiting\n", s);
        sleep(3);
        printf("Leaving quithandler\n");
}
