/*
 * =====================================================================================
 *
 *       Filename:  hello4.c
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

int main() {
        int i;
        initscr();
        clear();
        for (i = 0; i < LINES; ++i) {
                move(i, i + 1);
                if (i % 2 == 1) standout();
                addstr("Hello world");
                if (i % 2 == 1) standend();
                refresh();
                sleep(1);
                move(i, i + 1);
                addstr("                   ");
        }
        endwin();
        return 1;
}
