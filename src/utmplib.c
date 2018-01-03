/*
 * =====================================================================================
 *
 *       Filename:  utmplib.c
 *
 *    Description:  utmp工具包
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
#include <sys/types.h>
#include <time.h>
#include <utmp.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

utmp_open(char *filename) {
  fd_utmp = open(filename, O_RDONLY);
  cur_rec = num_recs = 0;
  return fd_utmp;
}

struct utmp *utmp_next() {
  struct utmp *recp;
  if (fd_utmp == -1)
    return NULLUT;
  if (cur_rec == num_recs && utmp_reload() == 0)
    return NULLUT;

  recp = (struct utmp *)&utmpbuf[cur_rec * UTSIZE];
  cur_rec++;
  return recp;
}

int utmp_reload() {
  int amt_read;
  amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
  num_recs = amt_read / UTSIZE;
  cur_rec = 0;
  return num_recs;
}

utmp_close() {
  if (fd_utmp != -1)
    close(fd_utmp);
}

int logout_tty(char *line) {
  int fd;
  struct utmp rec;
  int len = sizeof(struct utmp);
  int retval = -1;

  if ((fd = open(UTMP_FILE, O_RDWR)) == -1)
    return -1;

  /* search and replace  */
  while (read(fd, &rec, len) == len) {
    if (strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0) {
      rec.ut_type == DEAD_PROCESS;
      if (time(&rec.ut_time) != -1)
        if (lseek(fd, -len, SEEK_CUR) != -1)
          if (write(fd, &rec, len) == len)
            retval = 0;
      break;
    }
  }

  /* close file */
  if (close(fd) == -1)
    retval = -1;
  return retval;
}
