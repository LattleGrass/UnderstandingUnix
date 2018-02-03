/*
 * =====================================================================================
 *
 *       Filename:  echostate.c
 *
 *    Description:  unix编程实践里面的显示回显位状态的例子
 *
 *        Version:  1.0
 *        Created:  2018-02-03
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

int main() {
        struct termios info;
        int rv;

        /* tcgetattr函数用于获取与终端相关的参数。参数fd为终端的文件描述符，返回的结果保存在termios结构体中

           tcflag_t c_iflag;
           tcflag_t c_oflag;
           tcflag_t c_cflag;
           tcflag_t c_lflag;
           cc_t     c_cc[NCCS];

           c_iflag：输入模式标志，控制终端输入方式
           c_oflag：输出模式标志，控制终端输出方式
           c_cflag：控制模式标志，指定终端硬件控制信息
           c_lflag：本地模式标志，控制终端编辑功能
           c_cc[NCCS]：控制字符，用于保存终端驱动程序中的特殊字符
         */
        rv = tcgetattr(0, &info);
        if (rv == -1) {
                perror("tcgetattr error");
                exit(1);
        }

        if (info.c_cflag & ECHO)
                printf("echo is on, since its bit is 1\n");
        else
                printf("echo is off, since its bit is 0\n");
        return 0;
}
