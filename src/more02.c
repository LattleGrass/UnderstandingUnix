/*
 * =====================================================================================
 *
 *       Filename:  more02.c
 *
 *    Description:  more的实现第二版
 *
 *        Version:  1.0
 *        Created:  2017-12-27
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
int see_more(FILE *);

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
	char line[LINELEN];
	int num_of_lines = 0;
	int see_more(FILE *), reply;

	FILE *fp_tty;
	fp_tty = fopen("/dev/tty", "r"); // 键盘
	if (fp_tty == NULL)
		exit(1);
	while (fgets(line, LINELEN, fp)) {
		if (num_of_lines == PAGELEN) {
			reply = see_more(fp_tty); // 从键盘读入命令
			if (reply == 0)
				break;
			num_of_lines -= reply;
		}
		if (fputs(line, stdout) == EOF) {
			exit(1);
		}
		num_of_lines++;
	}
}

int see_more(FILE *cmd) {
	int c;
	printf("\033[7m more? \033[m");
	while ((c = getc(cmd)) != EOF) {
		if (c == 'q') {
			return 0;
		}
		if (c == ' ') {
			return PAGELEN;
		}
		if (c == '\n') {
			return 1;
		}
	}
	return 0;
}
