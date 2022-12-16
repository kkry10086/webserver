
#ifndef GUARD__PTHREAD_H
#define GUARD__PTHREAD_H


#include<pthread.h>
#include<unistd.h>
#include<sys/epoll.h>
#include"task.h"
#include"taskList.h"

#define PMAXNUM 20
#define PMINNUM 3

/*这里是多线程的环境，所以有一些成员变量是要加锁的,例如：pnum,Pshut(可能不需要加锁),closenum。
headfile：<pthread.h>
有pthread_mutex_t,pthread_mutex_init,pthread_mutex_destroy,pthread_mutex_lock,pthread_mutex_unlock。
*/
//定义锁
extern pthread_mutex_t pnum_mutex,closenum_mutex;


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

    //TaskList任务数组类型的对象的指针,将数据
    //封装到最后，现在只有一个方法：让pthread也变成类模板，这样就可以使用tasklist的对象。或者让pthread成为tasklist的友元类,但是仍然无法解决有T的问题。所以可能可以使用类的继承。基类可以是Task
    TaskList<struct epoll_event> *tl;
    
public:
    //初始化
    Pth();
    Pth(TaskList<struct epoll_event> *kk);
    //管理线程
    void *Pmanager(void* arg);

    //执行任务的线程
    void *Pdotask(void *arg);

    //对于closenum的操作
    void set_closenum(size_t count);
    const size_t get_closenum();
    void sub_closenum();
    

    //对于pnum的操作
    void set_pnum(size_t count);
    const size_t get_pnum();
    void sub_pnum();

    //对于Pshut的操作
    void set_Pshut(int state);
    int get_Pshut();


    //using in actually

    //判断closenum是否为空，关不关闭自己
    void ifexitByclosenum();
    
};
//配合pthread_create使用的函数
static void *dopth(void * arg){
    std::cout<<"do p"<<std::endl; 
    Pth *temp = (Pth *)arg;
    std::cout<<"pp"<<std::endl;
    temp->Pdotask(NULL);
    std::cout<<"ppp"<<std::endl;
}
static void *doMpth(void * arg)
{
    std::cout<<"do Mp"<<std::endl;
    Pth *temp = (Pth *)arg;
    std::cout<<"MMp"<<std::endl;
    temp->Pmanager(NULL);
    std::cout<<"MMMp"<<std::endl;
}

#endif
