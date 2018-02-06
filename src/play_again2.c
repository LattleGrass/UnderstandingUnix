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
void tty_mode(int);

int main() {
        int response;
        tty_mode(0);
        set_crmode();
        response = get_response(QUESTION);
        tty_mode(1);
        return response;
}

int get_response(char *question) {
        int input;
        printf("%s(y/n)?", question);
        while (1) {
                switch (input = getchar()) {
                        case 'y':
                        case 'Y':
                                return 0;
                        case 'n':
                        case 'N':
                                return 1;
                        default:
                                printf("\ncannot understand %c, ", input);
                                printf("please type y or n\n");
                }
        }
}

void set_crmode() {
        struct termios ttystate;
        tcgetattr(0, &ttystate);
        ttystate.c_cflag &= ~ICANON;
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how) {
        static struct termios original_mode;
        if (how == 0)
                tcgetattr(0, &original_mode);
        else
                tcsetattr(0, TCSANOW, &original_mode);
}
