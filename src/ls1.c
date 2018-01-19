/*
 * =====================================================================================
 *
 *       Filename:  ls1.c
 *
 *    Description:  ls的简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void do_ls(char[]);

int main(int ac, char *av[]) {
	if (ac == 1)
		do_ls(".");
	else
		while (--ac) {
			printf("%s:\n", *++av);
			do_ls(*av);
		}
	return 0;
}

void do_ls(char dirname[]) {
	DIR *dir_ptr;
	struct dirent *direntp;

	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1, cannot open %s\n", dirname);
	else {
		while ((direntp = readdir(dir_ptr)) != NULL)
			printf("%s\n", direntp->d_name);
		closedir(dir_ptr);
	}
}
