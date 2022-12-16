#ifndef GUARD_TASK_H
#define GUARD_TASK_H

#include<semaphore.h>
#include<unistd.h>

#include<iostream>
#include<sys/epoll.h>

#define TASKLEN 30

/*这里的fst,fin在多线程里面要加锁
而在这里有取与存的操作，所以我们可以使用
信号量或者条件变量来实现

tnum也要加锁。
*/

sem_t getsem,setsem;

pthread_mutex_t tnum_mutex;


///////////////////////////

template<typename T>
class TaskList
{
    
private:
    //取的位置,最后一个的索引,总的数量
    size_t fst{0},fin{0},tnum{0};

    //决定使用数组
    T taskarray[TASKLEN];

    

public:
    typedef size_t size_type;
   
     
    TaskList();
    
    //修改，获得fst
     
    const size_t get_fst();
     
    void add_fst();

    //修改，获得fin
     
    const size_t get_fin();
     
    void add_fin();

    //fst和fin是否相等,相等返回值为0
     
    int fef();

    //判断list是否满了,满了返回0
     
    int isfill();

    //得到task的数量
     
    size_t get_tnum();
    //插入一个task
     
    void push_back(T* tt);

    //取出一个task
     
    T& pop_one();

    
};


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
    int (*fun)(char *buf);
    
public:
    //Task();
    ~Task();
    void set_fd(const int cfd);
    int get_fd();
    void set_fun(int (*abc)(char *buf));
    
    void do_fun();
    void set_event(const int events);
    const int get_event();

    void set_buf(char *bf);
        
};
//#include"task.hpp"
//sem_t getsem,setsem;

//pthread_mutex_t tnum_mutex;
template< class T>
TaskList<T>::TaskList()
{
    //初始化
    sem_init(&setsem,0,TASKLEN);
    sem_init(&getsem,0,0);
    pthread_mutex_init(&tnum_mutex,NULL);
}
template<class T>
const size_t TaskList<T>::get_fst()
{
    return fst;
}
template<class T>
void TaskList<T>::add_fst()
{
    fst=(fst+1)%TASKLEN;
}
template<class T>
const size_t TaskList<T>::get_fin()
{
    return fin;
}
template<class T>
void TaskList<T>::add_fin()
{
    fin=(fin+1)%TASKLEN;
}
template<class T>
int TaskList<T>::fef()
{
    return (fst-fin);
}
template<class T>
int TaskList<T>::isfill()
{
    if(1 == (fst-fin))
        return 0;
    else
        return 1; 
}

template<class T>
size_t TaskList<T>::get_tnum()
{
    return tnum;
}

//插入一个任务
template<class T>
void TaskList<T>::push_back(T* tt)
{
    sem_wait(&setsem);
    if(isfill())
    {
        fin++;
        memcpy(taskarray+fin,tt,sizeof(T));
        pthread_mutex_lock(&tnum_mutex);
        tnum++;
        pthread_mutex_unlock(&tnum_mutex);
        
    }
    sem_post(&getsem);
}
//取出一个任务
template<class T>
T& TaskList<T>::pop_one()
{
    sem_wait(&getsem);
    if(fef())
    {
        pthread_mutex_lock(&tnum_mutex);
        tnum--;
        return taskarray[fst++];
        pthread_mutex_unlock(&tnum_mutex);
    }
    sem_post(&setsem);
}





/*下面就是针对task的修改
*/

Task::~Task()
{
    close(fd);
}
void Task::set_fun(int (*abc)(char *buf))
{
    fun = abc;
}
int print(char *buf)
{
    std::cout<<buf<<std::endl;
    return 1;
}
void Task::do_fun(){
    fun(buf);
}

void Task::set_event(const int events)
{
    epollev = events;
}
const int Task::get_event()
{
    return epollev;
}
void Task::set_fd(const int cfd)
{
    fd = cfd;
}
int Task::get_fd()
{
    return fd;
}
void Task::set_buf(char *bf)
{
    buf = bf;
}
#endif
