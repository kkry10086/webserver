#ifndef __WRAP_H
#define __WRAP_H
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<errno.h>

int Bind(int ,const struct sockaddr *,socklen_t );
int Accept(int ,struct sockaddr* ,socklen_t *);
int Socket(int,int,int);
int Connect(int,struct sockaddr *,socklen_t);
int Listen(int,int);
int Write(int ,const void *,size_t);
int Read(int ,void*, size_t);
int Epoll_create(size_t n);
int Epoll_wait(int epfd,epoll_event *evs,int maxevents,int timeout);
short chptrtos(char *ch);
char *stochptr(char *res,const short &num);
short crc(unsigned  short *buf,size_t len);

#endif
