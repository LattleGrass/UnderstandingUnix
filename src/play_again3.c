/*
 * =====================================================================================
 *
 *       Filename:  play_again3.c
 *
 *    Description:  play_again的非阻塞版本
 *
 *        Version:  1.0
 *        Created:  2018-02-07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int get_response(char* question, int maxtries);
int get_ok_char(void);
void set_cr_noecho_mode();
void set_nodelay_mode();
int tty_mode(int how);

int main() {
        int response;
        tty_mode(0);
        set_cr_noecho_mode();
        set_nodelay_mode();
        response = get_response(ASK, TRIES);
        tty_mode(1);
        return response;
}

int get_response(char* question, int maxtries) {
        int input;
        printf("%s (y/n)?", question);
        /* fflush()用于清空文件缓冲区，如果文件是以写的方式打开
         * 的，则把缓冲区内容写入文件。其原型为： */
        /*     int fflush(FILE* stream); */
        /* 【参数】stream为文件指针。 */
        /* 【返回值】成功返回0，失败返回EOF，错误代码存于errno
         * 中。指定的流没有缓冲区或者只读打开时也返回0值。 */
        fflush(stdout);
        while (1) {
                sleep(SLEEPTIME);
                input = tolower(get_ok_char());
                if (input == 'y') return 0;
                if (input == 'n') return 1;
                if (maxtries-- == 0) return 2;
                BEEP;
        }
}

int get_ok_char() {
        int c;
        while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL)
                ;
        return c;
}

void set_cr_noecho_mode() {
        struct termios ttystate;
        /* tcgetattr() gets the parameters associated with the object referred
         * by fd and stores them in the termios structure referenced by
         * termios_p. */
        tcgetattr(0, &ttystate);
        // ICANON Enable canonical mode
        ttystate.c_lflag &= ~ICANON;
        /* Echo input characters */
        ttystate.c_lflag &= ~ECHO;
        /* Minimum number of characters for noncanonical read */
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &ttystate);
}

void set_nodelay_mode() {
        int termflags;
        termflags = fcntl(0, F_GETFL);
        termflags |= O_NDELAY;
        fcntl(0, F_SETFL, termflags);
}

int tty_mode(int how) {
        static struct termios original_mode;
        static int original_flags;
        if (how == 0) {
                /* The tcsetattr() function sets the parameters associated with
                 * the terminal referred to by the specified file descriptor
                 * from the termios structure, according to the following
                 * requested action: */
                tcgetattr(0, &original_mode);
                /* fcntl 功能：操纵文件描述符，改变已打开的文件的属性 */
                /* 1.复制一个现有的描述符（cmd=F_DUPFD）. */
                /* 2.获得／设置文件描述符标记(cmd=F_GETFD或F_SETFD).*/
                /* 3.获得／设置文件状态标记(cmd=F_GETFL或F_SETFL).*/
                /* 4.获得／设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN).*/
                /* 5.获得／设置记录锁(cmd=F_GETLK,F_SETLK或F_SETLKW).*/
                original_flags = fcntl(0, F_GETFL);
                return 0;
        } else {
                tcsetattr(0, TCSANOW, &original_mode);
                fcntl(0, F_SETFL, original_flags);
                return 0;
        }
}
