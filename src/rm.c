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
    /* unlink()会删除参数pathname 指定的文件. 如果该文件名为最后连接点,
     * 但有其他进程打开了此文件, 则在所有关于此文件的文件描述词皆关闭后才会删除.
     * 如果参数pathname 为一符号连接, 则此连接会被删除。 */
    if ((rt = unlink(argv[1])) != 0) {
      fprintf(stderr, "error.");
      exit(3);
    }
  }
  return 0;
}
