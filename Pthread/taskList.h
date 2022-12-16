#ifndef GUARD_TASKLIST_H
#define GUARD_TASKLIST_H

#include<semaphore.h>
#include<unistd.h>

#include"task.h"
#include<iostream>
#include<sys/epoll.h>

#define TASKLEN 30

/*这里的fst,fin在多线程里面要加锁
而在这里有取与存的操作，所以我们可以使用
信号量或者条件变量来实现

tnum也要加锁。
*/
extern sem_t getsem,setsem;
extern pthread_mutex_t tnum_mutex;





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
     
    T& pop_one(T* ep);

    
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
    if((fin+1)%TASKLEN == fst)
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
    int temp;
    sem_getvalue(&setsem,&temp);
    std::cout<<"setsem::"<<temp<<std::endl;
    sem_wait(&setsem);
    if(isfill())
    {
        std::cout<<"push one"<<std::endl;
        
        memcpy(taskarray+fin,tt,sizeof(T));
        pthread_mutex_lock(&tnum_mutex);
        tnum++;
        pthread_mutex_unlock(&tnum_mutex);
        fin++;
    
    }
    else{
        std::cout<<"isfill"<<std::endl;
    }
    sem_post(&getsem);
}
//取出一个任务
template<class T>
T& TaskList<T>::pop_one(T * ep)
{
    int temp;
    sem_getvalue(&getsem,&temp);
    std::cout<<"getsem::"<<temp<<std::endl;
    sem_wait(&getsem);
    
    if(fef()!=0)
    {
        std::cout<<"test"<<std::endl;
        pthread_mutex_lock(&tnum_mutex);
        std::cout<<"tnum::"<<tnum<<std::endl;
        tnum--;
        std::cout<<"tnum::"<<tnum<<std::endl;
        *ep = taskarray[fst];
        fst++;
        std::cout<<"fst::"<<fst<<std::endl;
        pthread_mutex_unlock(&tnum_mutex);
        
    }
    sem_post(&setsem);
}


#endif
