/*
 * =====================================================================================
 *
 *       Filename:  bounce_async.c
 *
 *    Description:  异步信号处理初步
 *
 *        Version:  1.0
 *        Created:  2018-03-21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
#include <curses.h>
#include <fcntl.h>
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

int row = 10;
int col = 0;
int dir = 1;
int delay = 200;
int done = 0;

void enable_kbd_signals();
void on_input(int signum);
void on_alarm(int signum);
int set_ticker(int n_msecs);

int main() {
        void on_alarm(int);
        void on_input(int);
        void enable_kbd_signals();

        initscr();
        crmode();
        noecho();
        clear();

        signal(SIGIO, on_input);
        enable_kbd_signals();
        signal(SIGALRM, on_alarm);
        set_ticker(delay);

        move(row, col);
        addstr(MESSAGE);
        while (!done) pause();
        endwin();
}

void on_input(int signum) {
        int c = getch();
        if (c == 'Q' || c == EOF)
                done = 1;
        else if (c == ' ')
                dir = -dir;
}

void on_alarm(int signum) {
        signal(SIGABRT, on_alarm);
        mvaddstr(row, col, BLANK);
        col += dir;
        mvaddstr(row, col, MESSAGE);
        refresh();

        /* now handle borders */

        if (dir == -1 && col <= 0)
                dir = 1;
        else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
                dir = -1;
}

void enable_kbd_signals() {
        int fd_flags;

        fcntl(0, F_SETOWN, getpid());
        fd_flags = fcntl(0, F_GETFL);
        fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
}

int set_ticker(int n_msecs) {
        struct itimerval new_timeset;
        long n_sec, n_usecs;

        n_sec = n_msecs / 1000;
        n_usecs = (n_msecs % 1000) * 1000L;
        new_timeset.it_interval.tv_sec = n_sec;
        new_timeset.it_interval.tv_usec = n_usecs;

        new_timeset.it_value.tv_sec = n_sec;
        new_timeset.it_value.tv_usec = n_usecs;
        return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
