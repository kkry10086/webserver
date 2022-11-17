#ifndef __WRAP_H
#define __WRAP_H
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
int Bind(int ,const struct sockaddr *,socklen_t );
int Accept(int ,struct sockaddr* ,socklen_t *);
int Socket(int,int,int);
int Connect(int,struct sockaddr *,socklen_t);
int Listen(int,int);
int Write(int ,const void *,size_t);
int Read(int ,void*, size_t);
#endif
