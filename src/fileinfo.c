/*
 * =====================================================================================
 *
 *       Filename:  fileinfo.c
 *
 *    Description:  读取文件信息
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void show_stat_info(char *fname, struct stat *buf);

int main(int ac, char *av[]) {
	struct stat info;

	if (ac > 1) {
		// stat 通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
		if (stat(av[1], &info) != -1) {
			show_stat_info(av[1], &info);
			return 0;
		} else {
			perror(av[1]);
		}
		return 1;
	}
}

void show_stat_info(char *fname, struct stat *buf) {
	printf("  mode: %o\n", buf->st_mode);
	printf("   links: %d\n", buf->st_nlink);
	printf("    user: %d\n", buf->st_uid);
	printf("   group: %d\n", buf->st_gid);
	printf("    size: %d\n", buf->st_size);
	printf(" modtime: %d\n", buf->st_mtime);
	printf("    name: %s\n", fname);
}
