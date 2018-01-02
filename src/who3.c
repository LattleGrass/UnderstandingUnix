/*
 * =====================================================================================
 *
 *       Filename:  who3.c
 *
 *    Description:  加上缓存后的who实现
 *
 *        Version:  1.0
 *        Created:  2018-01-02
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
#include <utmp.h>

#define SHOWHOST
#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

void show_info(struct utmp *);
void showtime(time_t);

int main() {
  struct utmp *utbufp, *utmp_next();
  if (utmp_open(UTMP_FILE) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }

  while ((utbufp = utmp_next()) != ((struct utmp *)NULL)) {
    show_info(utbufp);
  }
  utmp_close();
  return 0;
}

void show_info(struct utmp *utbufp) {
  if (utbufp->ut_type != USER_PROCESS) {
    return;
  }
  printf("% -8.8s", utbufp->ut_name); /* name */
  printf(" ");
  printf("% -8.8s", utbufp->ut_line); /* tty */
  printf(" ");
  show_time(utbufp->ut_time);
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", utbufp->ut_host); /* host */
#endif
  printf("\n");
}

show_time(long timeval) {
  /* display the time in a format fit for human */
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4);
}
