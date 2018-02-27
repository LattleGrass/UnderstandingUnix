/*
 * =====================================================================================
 *
 *       Filename:  hello5.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018-02-27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define LEFTEDGE 10
#define RIGHTEDGE 30
#define ROW 10

int main() {
        char *message = "Hello";
        char *blank = "     ";
        int dir = +1;
        int pos = LEFTEDGE;

        initscr();
        clear();
        while (1) {
                move(ROW, pos);
                addstr(message);
                move(LINES - 1, COLS - 1);
                refresh();
                sleep(1);
                move(ROW, pos);
                addstr(blank);
                pos += dir;
                if (pos >= RIGHTEDGE) dir = -1;
                if (pos <= LEFTEDGE) dir = +1;
        }
}
