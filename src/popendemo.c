/*
 * =====================================================================================
 *
 *       Filename:  popendemo.c
 *
 *    Description:  popen例子
 *
 *        Version:  1.0
 *        Created:  2018-04-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main() {
        FILE *fp;
        char buf[100];
        int i = 0;

        fp = popen("who|sort", "r");
        while (fgets(buf, 100, fp) != NULL) printf("%3d %s", i++, buf);
        pclose(fp);
        exit(0);
}
