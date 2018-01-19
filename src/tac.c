/*
 * =====================================================================================
 *
 *       Filename:  tac.c
 *
 *    Description:  tac命令简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

/* https://www.ibm.com/developerworks/cn/linux/l-cn-commands/index.html */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define SIZE 1000001
#define NLINE '\n'

int main(int argc, char **argv) {
	char buf[SIZE];
	char *p1, *p2, *p3, *p4;
	struct stat *fp;
	int fd;
	fp = (struct stat *)malloc(sizeof(struct stat));
	if (argc != 2) {
		fprintf(stderr, "input error\n");
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1) { // 打开文件
		fprintf(stderr, "open error %s\n", strerror(errno));
		exit(1);
	}
	/* int fstat(int fildes, struct stat *buf);
	 * 函数说明：fstat()用来将参数fildes 所指的文件状态, 复制到参数buf
	 * 所指的结构中(struct stat). Fstat()与stat()作用完全相同,
	 * 不同处在于传入的参数为已打开的文件描述词. 详细内容请参考stat(). */
	if (fstat(fd, fp) == -1) { // 获取文件状态
		fprintf(stderr, "fstat error %s \n", strerror(errno));
		exit(2);
	}
	if (fp->st_size > (SIZE - 1)) { // 缓存长度不足
		fprintf(stderr, "buffer size is not big enough\n");
		exit(3);
	}
	if ((read(fd, buf, fp->st_size)) == -1) { // 全部读入缓存
		fprintf(stderr, "read error\n");
		exit(4);
	}

	/* strchr() 用来查找某字符在字符串中首次出现的位置，其原型为： */
	/*   char * strchr (const char *str, int c); */
	/* strrchr() 函数用于查找某字符在字符串中最后一次出现的位置，其原型为： */
	/*     char * strrchr(const char *str, int c); */
	p1 = strchr(buf, NLINE);  // 第一个换行
	p2 = strrchr(buf, NLINE); // 最后一个换行
	*p2 = '\0';

	do {
		p2 = strrchr(buf, NLINE); // 最后一个换行
		p4 = p2;
		p3 = p2 + sizeof(char); // 最后一行的第一个字符
		printf("%s\n", p3);     // 打印最后一行
		*p4 = '\0';
	} while (p2 != p1);

	if (p2 == p1) {
		*p2 = '\0';
		printf("%s\n", buf);
	}
	return 0;
}
