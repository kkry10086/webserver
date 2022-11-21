
#ifndef GUARD__PTHREAD_H
#define GUARD__PTHREAD_H

#include<pthread.h>

#define PMAXNUM 20
#define PMINNUM 3

/*这里是多线程的环境，所以有一些成员变量是要加锁的,例如：pnum,Pshut(可能不需要加锁),closenum。
headfile：<pthread.h>
有pthread_mutex_t,pthread_mutex_init,pthread_mutex_destroy,pthread_mutex_lock,pthread_mutex_unlock。
*/
//定义锁
pthread_mutex_t pnum_mutex,closenum_mutex;


//初始化锁
pthread_mutex_init(&pnum_mutex,NULL);
pthread_mutex_init(&closenum_mutex,NULL);


///////////////


//线程的类
class Pth
{
private:
    //现有的线程数量
    size_t pnum{0};
    //最大的线程数量（除了最初的线程）
    size_t maxnum{PMAXNUM};
    //最小的线程数量（除了最初的线程）
    size_t minnum{PMINNUM};

    //是否关闭全部线程
    int Pshut{0};

    //要关闭的线程数量
    size_t closenum{0};
    
public:
    //管理线程
    void *PManager(void* arg);

    //执行任务的线程
    void *Pdotask(void *arg);

    //对于closenum的操作
    void set_closenum(size_t count);
    const size_t get_closenum();
    void sub_closenum();

    //对于pnum的操作
    void set_pnum(size_t count);
    const size_t get_pnum();

    //对于Pshut的操作
    void set_Pshut(int state);
    int get_Pshut();
};


#endif
