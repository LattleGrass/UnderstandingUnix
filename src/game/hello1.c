/*
 * =====================================================================================
 *
 *       Filename:  hello1.c
 *
 *    Description:  curse库的使用
 *
 *        Version:  1.0
 *        Created:  2018-02-24
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
        initscr();

        clear();
        move(10, 20);
        addstr("hello world");
        move(LINES - 1, 0);
        refresh();
        getch();
        endwin();
}
