/*
 * =====================================================================================
 *
 *       Filename:  head.c
 *
 *    Description:  head命令简单实现
 *
 *        Version:  1.0
 *        Created:  2018-01-04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0
#define READSIZE 4096

int main(int argc, char *argv[]) {
  int rfd = -1,      /* 文件描述符 */
      rlen = 0,      /* 每次read文件的内容长度 */
      i, nline = 10, /* 读取文件行数 */
      nent = 0, ret;

  char rbuf[READSIZE]; // 读文件缓冲区
  char c;
  char *pb = 0; // 指向文件每行换行
  char *filename;
  memset(rbuf, 0, READSIZE);

  while ((c = getopt(argc, argv, "n:")) != -1) {
    switch (c) {
    case 'n': // 指定行数
      nline = atoi(optarg);
      break;
    default:
      fprintf(stderr, "Usage: %s [-n lines]", argv[0]);
      return -1;
    }
  }

  filename = argv[optind];
  printf("filename: %s\n", filename);
  if ((rfd = open(filename, O_RDONLY)) == -1) {
    fprintf(stderr, "%s: ", argv[0]);
    return -1;
  }

  while ((rlen = read(rfd, rbuf, READSIZE)) > 0) {
    for (i = 0; i < rlen; i++) {
      if (rbuf[i] == '\n') {
        pb = &rbuf[i];
        if (++nent == nline)
          break;
      }
    }
    /* printf("nent: %d\n", nent); */
    if (nent == nline) {
      printf("%.*s", (int)(pb - &rbuf[0] + 1), rbuf);
      break;
    } else if (i == rlen) {
      printf("%s", rbuf);
    }
    memset(rbuf, 0, READSIZE);
  }
  ret = close(rfd);
  if (ret == -1) {
    perror("close file error: ");
  }
  return ret;
}
