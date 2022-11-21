#ifndef GUARD__TASK_H
#define GUARD__TASK_H 

#include<semaphore.h>
#include<unistd.h>


#define TASKLEN 30

/*这里的fst,fin在多线程里面要加锁
而在这里有取与存的操作，所以我们可以使用
信号量或者条件变量来实现
*/

sem_t getsem,setsem;




///////////////////////////

template<class T>
class TaskList
{
    
private:
    //取的位置,最后一个的索引
    size_t fst{0},fin{0};

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
    int fd;
    char *buf{0};
    unsigned int taskev{0};
    int (*fun)(char *buf);
    
public:
    ~Task();
    void set_fun(int (*abc)(char *buf));
    void do_fun();
        
};

#endif
