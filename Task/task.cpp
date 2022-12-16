#include"task.h"

/*下面就是针对task的修改
*/

Task::~Task()
{
    close(fd);
}
void Task::set_fun(int (*abc)(Task *bf))
{
    fun = abc;
}
int print(Task *tf)
{
    int cfd = tf->get_fd();
    char buf[1024];
    int ret = read(cfd,buf,1024);
    if(ret >0){
        std::cout<<buf<<std::endl;
        tf->set_buf(buf);
    }
    return 1;
}
void Task::do_fun(){
    fun(this);
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
