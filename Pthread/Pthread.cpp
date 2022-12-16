#include"Pthread.h"
#include<iostream>

pthread_mutex_t pnum_mutex,closenum_mutex;

sem_t getsem,setsem;
pthread_mutex_t tnum_mutex;

Pth::Pth()
{
    //初始化锁
    pthread_mutex_init(&pnum_mutex,NULL);
    pthread_mutex_init(&closenum_mutex,NULL);
}
Pth::Pth(TaskList<struct epoll_event> *kk)
{
    //初始化锁
    pthread_mutex_init(&pnum_mutex,NULL);
    pthread_mutex_init(&closenum_mutex,NULL);
    tl = kk;
}


//管理线程
/*设置pthread的生成与消灭规则
 */
void *Pth::Pmanager(void *arg)
{
    while(1){
        std::cout<<"doing manager"<<std::endl;

        pthread_mutex_lock(&tnum_mutex);
        pthread_mutex_lock(&pnum_mutex);
        //当tasknum/pthread>1.5，生成线程
        size_t tnum = tl->get_tnum();
        if(pnum!=0 && tnum/pnum >1.5)
        {
            //增加tnum/1.5-pnum个线程
            size_t temp =pnum+(tnum/1.5-pnum);
            if(temp > PMAXNUM){
                temp=PMAXNUM;
            }
            set_pnum(temp);

            //
            pthread_t tid;
            for(size_t i =0;i<temp;++i){
                pthread_create(&tid,NULL,dopth,this);
                pthread_detach(tid);
            }
        
        
        }

        //当tasknum<pthread,减少到双方相等
        else if(tnum<pnum)
        {
            pthread_mutex_lock(&closenum_mutex);
            //减少到双方相等
            if(tnum<3){
                set_pnum(3);
                set_closenum(pnum-3);
            }
            else
            {
                set_pnum(tnum);
                set_closenum(pnum-tnum);
            }
            pthread_mutex_unlock(&closenum_mutex);
        
        }
        pthread_mutex_unlock(&tnum_mutex);
        pthread_mutex_unlock(&pnum_mutex);

        sleep(1);
    }
}


//普通的做任务的线程
void *Pth::Pdotask(void *arg)
{
    sleep(2);
    while(1)
    {
        std::cout<<"dong dotask"<<std::endl;
        //1.判断是否要全部关闭
        if(Pshut){
            pthread_exit(NULL);
        }

        //2.判断closenum是否为空，自己要不要关闭
        ifexitByclosenum();
        std::cout<<"ifexitclose"<<std::endl;

        std::cout<<"fst::"<<tl->get_fst()<<",fin::"<<tl->get_fin()<<std::endl;
        //3.判断有没有task可以取，并获得一个task
        epoll_event task_e ;
        tl->pop_one(&task_e);
    
        //4.对task进行操作
        //Task *task = task_e->ptr;
        
        std::cout<<"pth"<<std::endl;
        Task * tt =(Task*)task_e.data.ptr;
        tt->do_fun();
    }
}

void Pth::set_closenum(size_t count)
{
    closenum=count;
}
const size_t Pth::get_closenum()
{
    //这里不使用加锁，是因为这个锁要用来比较
    //所以要把整个比较过程锁住
    return closenum;
}
void Pth::sub_closenum()
{
    closenum--;
}

//2.判断closenum是否为空，自己要不要关闭
void Pth::ifexitByclosenum()
{
    
    pthread_mutex_lock(&closenum_mutex);
    if(get_closenum()){
        sub_closenum();
        pthread_mutex_lock(&pnum_mutex);
        
        sub_pnum();
        pthread_mutex_unlock(&pnum_mutex);
        pthread_mutex_unlock(&closenum_mutex);
        pthread_exit(NULL);
    }
    pthread_mutex_unlock(&closenum_mutex);
}

//pnum
inline void Pth::set_pnum(size_t count)
{
    pnum =count;
   
}
inline const size_t Pth:: get_pnum()
{
    return pnum;
}
inline void Pth::sub_pnum()
{
    --pnum;
}

inline void Pth::set_Pshut(int state)
{
    Pshut = state;
}
inline int Pth::get_Pshut()
{
    return Pshut;
}
