/*
 * =====================================================================================
 *
 *       Filename:  more01.c
 *
 *    Description:  more命令的模拟实现第一版
 *
 *        Version:  1.0
 *        Created:  2017-12-26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define PAGELEN 24
#define LINELEN 512

void *checked_malloc(int len) {
	void *p = malloc(len);
	assert(p);
	return p;
}

void do_more(FILE *);
int see_more();

int main(int ac, char *av[]) {
	FILE *fp;
	if (ac == 1)
		do_more(stdin);
	else
		while (--ac)
			if ((fp = fopen(*++av, "r")) != NULL) {
				do_more(fp);
				fclose(fp);
			} else
				exit(1);
	return 0;
}

void do_more(FILE *fp) {
	/* read PAGELEN lines, then call see_more() for further instructions */
	char line[LINELEN];
	int num_of_lines = 0;
	int see_more(), reply;
	while (fgets(line, LINELEN, fp)) { // 从文件描述符中读出LLINELEN个数据
		if (num_of_lines == PAGELEN) { // 如果达到了一页的数量
			reply = see_more();          // 收集键盘指令
			if (reply == 0) {
				break;
			}
			num_of_lines -= reply;
		}
		if (fputs(line, stdout) == EOF) { // 打印出来内容
			exit(1);
		}
		num_of_lines++;
	}
}

int see_more() {
	/* print message,wait for response */
	int c;
	printf("\033[7m more? \033[m");
	while ((c = getchar()) != EOF) {
		if (c == 'q')
			return 0;
		if (c == ' ')
			return PAGELEN;
		if (c == '\n')
			return 1;
	}
	return 0;
}
