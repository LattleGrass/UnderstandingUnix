/*
 * =====================================================================================
 *
 *       Filename:  play_again.c
 *
 *    Description:  再来一局的实现
 *
 *        Version:  1.0
 *        Created:  2018-02-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define QUESTION "Do you want another transaction?"

int get_response(char *);
int main() {
        int response;
        response = get_response(QUESTION);
        return response;
}

int get_response(char *question) {
        printf("%s(y/n)?", question);
        while (1) {
                switch (getchar()) {
                        case 'y':
                        case 'Y':
                                return 0;
                        case 'n':
                        case 'N':
                        case EOF:
                                return 1;
                }
        }
}
