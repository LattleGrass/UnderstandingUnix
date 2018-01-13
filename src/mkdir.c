/*
 * =====================================================================================
 *
 *       Filename:  mkdir.c
 *
 *    Description:  mkdir的简单实现
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
  int rt;
  if ((rt = mkdir(argv[1], 10705)) == -1)
    fprintf(stderr, "cannot mkdir");
  return 0;
}
