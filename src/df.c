/*
 * =====================================================================================
 *
 *       Filename:  df.c
 *
 *    Description:  df的简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/vfs.h>

#define SIZE1 100
#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define FN "/etc/mtab"
#define SPACE ' '

int displayapartion(char *pt, char *pt1);

int main(void) {
  char tmpline[SIZE1];
  FILE *fp;
  char *pt1;
  char *pt2;
  char *pt3;

  if ((fp = fopen(FN, "r")) == NULL) { // 打开 /etc/matb
    fprintf(stderr, "%s \n", strerror(errno));
    exit(5);
  }

  while (fgets(tmpline, SIZE1, fp) != NULL) { // 从 /etc/mtab中读出内容
    pt1 = strchr(tmpline, SPACE);             // 找到第一个空格
    pt2 = pt1 + sizeof(char);
    *pt1 = '\0';
    pt3 = strchr(pt2, SPACE); // 找到下一个空格
    *pt3 = '\0';
    if (strstr(tmpline, "/dev") != NULL) { // 检索/dev出现的位置
      displayapartion(tmpline, pt2);       // 打印信息
    } else {
      /* printf("nothing\n"); */
    }
  }
  return 0;
}

int displayapartion(char *pt, char *pt1) {
  struct statfs buf;
  statfs(pt1, &buf); // 将信息读入buf
  int usage;
  usage = ceil((buf.f_blocks - buf.f_bfree) * 100 / buf.f_blocks); // 使用占比
  printf("%s ", pt); // 名称
  printf("%ld ", buf.f_blocks); // block数量
  printf("%ld ", buf.f_blocks - buf.f_bfree); // 已用
  printf("%d%% ", usage); // 使用占比 
  printf("%s ", pt1);  // 位置信息
  printf("\n");
  return 0;
}
