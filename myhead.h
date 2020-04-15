#ifndef __HTTP_H_
#define __HTTP_H_


void accept_request(void *);
int startup(u_short *);
int get_line(int, char *, int);
void error_die(const char *);
#endif
