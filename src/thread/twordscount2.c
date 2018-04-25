/*
 * =====================================================================================
 *
 *       Filename:  twordscount2.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018-04-25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

struct arg_set {
        char *fname;
        int count;
};

int main(int ac, char **av) {
        pthread_t t1, t2;
        struct arg_set arg1, arg2;
        void *count_words(void *);

        if (ac != 3) {
                printf("usage: %s file1 file2\n", av[0]);
                exit(1);
        }

        arg1.fname = av[1];
        arg1.count = 0;
        pthread_create(&t1, NULL, count_words, (void *)&arg1);

        arg2.fname = av[2];
        arg2.count = 0;
        pthread_create(&t2, NULL, count_words, (void *)&arg2);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        printf("%5d: %s\n", arg1.count, av[1]);
        printf("%5d: %s\n", arg2.count, av[2]);
        printf("%5d: total_words\n", arg1.count + arg2.count);
}

void *count_words(void *a) {
        struct arg_set *arg = a;
        FILE *fp;
        int c, prevc = '\0';

        if ((fp = fopen(arg->fname, "r")) != NULL) {
                while ((c = getc(fp)) != EOF) {
                        if (!isalnum(c) && isalnum(prevc)) {
                                arg->count++;
                        }
                        prevc = c;
                }
                fclose(fp);
        } else {
                perror(arg->fname);
        }
        return NULL;
}
