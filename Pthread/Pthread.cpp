#include"Pthread.h"


//管理线程
void *Pth::Pmanager(void *arg)
{
}


//普通的做任务的线程
void *Pth::Ptodtask(void *arg)
{
    //1.判断是否要全部关闭
    if(Pshut){
        pthread_exit(NULL);
    }

    //2.判断有没有task可以取

    //
}

void Pth::set_closenum(size_t count)
{
    //加锁
    pthread_mutex_lock(&closenum_mutex);
    closenum=count;
    pthread_mutex_unlock(&closenum_mutex);
}
const size_t Pth::get_closenum()
{
    //这里不使用加锁，是因为这个锁要用来比较
    //所以要把整个比较过程锁住
    return closenum;
}
void sub_closenum()
{
    pthread_mutex_lock(&closenum_mutex);
    closenum--;
    pthread_mutex_unlock(&closenum_mutex);
}

//pnum
void Pth::set_pnum(size_t count)
{
    //加锁
    pthread_mutex_lock(&pnum_mutex);
    pnum =count;
    pthread_mutex_unlock(&pnum_mutex);
}
const Pth::size_t get_pnum()
{
    return pnum;
}

void Pth::set_Pshut(int state)
{
    Pshut = state;
}
int Pth::get_Pshut()
{
    return Pshut;
}
