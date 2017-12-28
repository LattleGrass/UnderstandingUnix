/*
 * =====================================================================================
 *
 *       Filename:  who1.c
 *
 *    Description:  who的简单实现
 *
 *        Version:  1.0
 *        Created:  2017-12-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define SHOWHOST

void *checked_malloc(int len) {
  void *p = malloc(len);
  assert(p);
  return p;
}

int main() {
  struct utmp current_record; /* read info into here */
  int utmpfd;                 /* read from this descriptor */
  int reclen = sizeof(current_record);

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }
  while (read(utmpfd, &current_record, reclen) == reclen) {
    show_info(&current_record);
  }
  close(utmpfd);
  return 0;
}

show_info(struct utmp *utbufp) {
  printf("% -8.8s", utbufp->ut_name); /* name */
  printf(" ");
  printf("% -8.8s", utbufp->ut_line); /* tty */
  printf(" ");
  printf("%10ld", utbufp->ut_time); /* login_time */
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", utbufp->ut_host); /* host */
#endif
  printf("\n");
}
