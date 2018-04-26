#ifndef _Webserv_
#define _Webserv_

#include <stdio.h>

void read_til_crnl(FILE *);
void process_rq(char *, int);
void do_404(char *, int);
void not_implemented(int);
void do_cat(char *, int);
int isadir(char *);
int not_exist(char *);
char *file_type(char *);
void skip_rest_of_header(FILE *);
void sanitize(char *);
int built_in(char *, int);
int http_reply(int, FILE **, int, char *, char *, char *);
void do_ls(char *, int);

int make_server_socket_q(int, int);
int make_server_socket(int);

#endif
