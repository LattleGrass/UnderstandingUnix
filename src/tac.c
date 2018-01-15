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
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    fprintf(stderr, "open error %s\n", strerror(errno));
    exit(1);
  }
  if (fstat(fd, fp) == -1) {
    fprintf(stderr, "fstat error %s \n", strerror(errno));
    exit(2);
  }
  if (fp->st_size > (SIZE - 1)) {
    fprintf(stderr, "buffer size is not big enough\n");
    exit(3);
  }
  if ((read(fd, buf, fp->st_size)) == -1) {
    fprintf(stderr, "read error\n");
    exit(4);
  }

  p1 = strchr(buf, NLINE);
  p2 = strrchr(buf, NLINE);
  *p2 = '\0';

  do {
    p2 = strrchr(buf, NLINE);
    p4 = p2;
    p3 = p2 + sizeof(char);
    printf("%s\n", p3);
    *p4 = '\0';
  } while (p2 != p1);

  if (p2 == p1) {
    *p2 = '\0';
    printf("%s\n", buf);
  }
  return 0;
}
