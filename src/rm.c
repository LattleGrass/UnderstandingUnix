/*
 * =====================================================================================
 *
 *       Filename:  rm.c
 *
 *    Description:  rm命令简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* https://www.ibm.com/developerworks/cn/linux/l-cn-commands/index.html */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
  int rt;
  if (argc != 2)
    exit(2);
  else {
    if ((rt = unlink(argv[1])) != 0) {
      fprintf(stderr, "error.");
      exit(3);
    }
  }
  return 0;
}
