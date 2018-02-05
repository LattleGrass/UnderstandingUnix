/*
 * =====================================================================================
 *
 *       Filename:  tty_mode.c
 *
 *    Description:  终端驱动模式实验
 *
 *        Version:  1.0
 *        Created:  2018-02-05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main() {
        int c;
        while ((c = getchar()) != EOF) {
                if (c == 'z')
                        c = 'a';
                else if (islower(c))
                        c++;
                putchar(c);
        }
        return 1;
}
