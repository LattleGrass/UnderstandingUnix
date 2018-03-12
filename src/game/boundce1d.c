/*
 * =====================================================================================
 *
 *       Filename:  boundce1d.c
 *
 *    Description:  在一条线上控制动画
 *
 *        Version:  1.0
 *        Created:  2018-03-12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define MESSAGE "hello"
#define BLANK "     "

int row;
int col;
int dir;
int set_ticker(int n_msecs);

int main() {
        int delay;
        int ndelay;

        int c;
        void move_msg(int);

        initscr();
        crmode();
        noecho();
        clear();

        row = 10;
        col = 10;
        dir = 1;
        delay = 200;

        move(row, col);
        addstr(MESSAGE);
        signal(SIGALRM, move_msg);
        set_ticker(delay);

        while (1) {
                ndelay = 0;
                c = getch();
                if (c == 'Q') break;
                if (c == ' ') dir = -dir;
                if (c == 'f' && delay > 2) ndelay = delay / 2;
                if (c == 's') ndelay = delay * 2;
                if (ndelay > 0) set_ticker(delay = ndelay);
        }
        endwin();
        return 0;
}

void move_msg(int signum) {
        signal(SIGALRM, move_msg);
        move(row, col);
        addstr(BLANK);
        col += dir;
        move(row, col);
        addstr(MESSAGE);
        refresh();

        if (dir == -1 && col <= 0)
                dir = 1;
        else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
                dir = -1;
}
