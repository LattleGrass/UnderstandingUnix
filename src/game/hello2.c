/*
 * =====================================================================================
 *
 *       Filename:  hello2.c
 *
 *    Description:  curses库体验
 *
 *        Version:  1.0
 *        Created:  2018-02-26
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

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main() {
        int i;
        initscr();
        clear();
        for (i = 0; i < LINES; i++) {
                move(i, i + 1);
                if (i % 2 == 1) standout();
                addstr("a wang a wang");
                if (i % 2 == 1) standend();
        }
        refresh();
        getch();
        endwin();
}
