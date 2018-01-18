/*
 * =====================================================================================
 *
 *       Filename:  who.c
 *
 *    Description:  who命令的简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-18
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
#include <time.h>
#include <unistd.h>
#include <utmp.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define SHOWHOST

void show_time(long timeval);
void show_info(struct utmp *uBuf);

int main(void) {
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof(current_record);
  /* 打开utmp_file 登录信息存在里面 */
  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    printf("open file error\n");
    exit(1);
  }
  while (read(utmpfd, &current_record, reclen) == reclen) // 读出一个用户信息
    show_info(&current_record);
  close(utmpfd);
  return 0;
}

void show_info(struct utmp *uBuf) {
  if (uBuf->ut_type != USER_PROCESS) {
    return;
  }
  printf("%-8.8s", uBuf->ut_name); // 用户名
  printf(" ");
  printf("%-8.8s", uBuf->ut_line);
  printf("     ");

  show_time(uBuf->ut_time); // 打印时间
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", uBuf->ut_host);
  printf(" ");
#endif
  printf("\n");
}

void show_time(long timeval) {
  struct tm *t;

  t = localtime(&timeval);

  if (t->tm_mon + 1 < 10)
    printf("%d-0%d", t->tm_year + 1900, t->tm_mon + 1);
  else
    printf("%d-%d", t->tm_year + 1900, t->tm_mon + 1);

  printf("-");
  if (t->tm_mday + 1 < 10)
    printf("0%d", t->tm_mday);
  else
    printf("%d", t->tm_mday);

  printf(" ");

  if (t->tm_hour < 10)
    printf("0%d", t->tm_hour);
  else
    printf("%d", t->tm_hour);

  printf(":");

  if (t->tm_min < 10)
    printf("0%d", t->tm_min);
  else
    printf("%d", t->tm_min);
}
