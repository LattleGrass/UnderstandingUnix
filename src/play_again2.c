/*
 * =====================================================================================
 *
 *       Filename:  play_again2.c
 *
 *    Description:  play_again的即时响应版本
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
#include <termios.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

#define QUESTION "Do you want another transaction?"

void set_crmode(void);
int get_response(char *);

int main() {
        int response;
        tty_mode(0);
        set_crmode();
        response = get_response(QUESTION);
        tty_mode(1);
        return response;
}
