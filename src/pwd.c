/*
 * =====================================================================================
 *
 *       Filename:  pwd.c
 *
 *    Description:  pwd实现版本1
 *
 *        Version:  1.0
 *        Created:  2018-01-25
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
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);

int main() {
	printpathto(get_inode("."));
	putchar('\n');
	return 0;
}

void printpathto(ino_t this_inode) {
	ino_t my_inode;
	char its_name[BUFSIZ];

        if (get_inode("..") != this_inode) { // 判断是否为根目录
		chdir("..");                       // 切换到上一层
		inum_to_name(this_inode, its_name, BUFSIZ); // 读取当前目录名
		my_inode = get_inode(".");                  // 递归
		printpathto(my_inode);
		printf("/%s", its_name);
        }
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen) {
	DIR *dir_ptr;
	struct dirent *direntp;

	dir_ptr = opendir(".");
	if (dir_ptr == NULL) {
		perror(".");
		exit(1);
	}

	while ((direntp = readdir(dir_ptr)) != NULL)
		if (direntp->d_ino == inode_to_find) {
			strncpy(namebuf, direntp->d_name, buflen);
			namebuf[buflen - 1] = '\0';
			closedir(dir_ptr);
			return;
		}
	fprintf(stderr, "error looking for inum %llu\n", inode_to_find);
	exit(1);
}

ino_t get_inode(char *fname) {
	struct stat info;

	if (stat(fname, &info) == -1) {
		fprintf(stderr, "Cannot stat");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}
