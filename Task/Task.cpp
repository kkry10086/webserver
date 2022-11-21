#include"Task.h"
template< class T>
TaskList<T>::TaskList()
{
    //初始化
    sem_init(&getsem,0,TASKLEN);
    sem_init(&setsem,0,0);
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

//插入一个任务
template<class T>
void TaskList<T>::push_back(T* tt)
{
    sem_wait(&setsem);
    //没有满,没有实现加锁的功能，后续实现
    if(isfill())
    {
        fin++;
        memcpy(taskarray+fin,tt,sizeof(T));
        
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
        return taskarray[fst++];
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
void Task::do_fun(){
    fun(buf);
}
