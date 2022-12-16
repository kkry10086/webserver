#ifndef GUARD_TASK_H
#define GUARD_TASK_H

#include<unistd.h>

#include<iostream>

//这里的数据都是独立的，有一个线程来处理的，
//所以不需要加锁
class Task
{
private:
    //文件描述符
    int epollev{0};
    int fd;
    char *buf{0};
    unsigned int taskev{0};
    int (*fun)(Task *tf);
    
public:
    //Task();
    ~Task();
    void set_fd(const int cfd);
    int get_fd();
    void set_fun(int (*abc)(Task *bf));
    
    void do_fun();
    void set_event(const int events);
    const int get_event();

    void set_buf(char *bf);
        
};
int print(Task  *tf);
#endif
