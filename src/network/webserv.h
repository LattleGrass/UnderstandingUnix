#ifndef _Webserv_
#define _Webserv_

#include <stdio.h>

void read_til_crnl(FILE *);
void process_rq(char *, int);
void header(FILE *, char *);
void cannot_do(int);
void do_404(char *, int);
void do_exec(char *, int);
void do_cat(char *, int);
int isadir(char *);
int not_exist(char *);
int do_ls(char *, int);
int ends_in_cgi(char *);
char *file_type(char *);

int make_server_socket_q(int, int);
int make_server_socket(int);

#endif
