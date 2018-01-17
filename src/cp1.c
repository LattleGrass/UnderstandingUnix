/*
 * =====================================================================================
 *
 *       Filename:  cp1.c
 *
 *    Description:  cp命令的简单实现
 *
 *        Version:  1.0
 *        Created:  2017-12-29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define BUFFSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int ac, char *av[]) {
  int in_fd, out_fd, n_char;
  char buf[BUFFSIZE];

  if (ac != 3) {
    fprintf(stderr, "usage: %s source destination\n", *av);
    exit(1);
  }

  if ((in_fd = open(av[1], O_RDONLY)) == -1) // 打开文件，获得文件描述符
    oops("Cannot open ", av[1]);

  if ((out_fd = creat(av[2], COPYMODE)) == -1) { // 创建要复制的文件，获得文件描述符
    oops("Cannot creat ", av[2]);
  }

  while ((n_char = read(in_fd, buf, BUFFSIZE)) > 0) { // 从源文件中读出buffsize长度的内容
    if (write(out_fd, buf, n_char) != n_char) { // 写入目标文件中
      oops("write error to ", av[2]);
    }
  }

  /* printf("n_char: %d\n", n_char); */

  if (n_char == -1) {
    oops("read error from ", av[1]);
  }

  if (close(in_fd) == -1 || close(out_fd) == -1) { // 关闭两个文件描述符
    oops("Error closing files", "");
  }
}

void oops(char *s1, char *s2) {
  fprintf(stderr, "Error: %s", s1);
  perror(s2);
  exit(1);
}
