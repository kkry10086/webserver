
#include"wrap.h"
#include"task.h"
#include"taskList.h"
#include"Pthread.h"

#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<cstring>


//sem_t getsem,setsem;
//pthread_mutex_t tnum_mutex;

using std::cin;using std::cout;
using std::endl;using std::string;

#define EVENTLEN 1024

//epoll树的根节点
int epfd=Epoll_create(1024);

//暂时存储有变化的event
struct epoll_event evs[EVENTLEN];


//声明TaskList
TaskList<struct epoll_event> taskl;




int main(int argc, char ** argv)
{
    //1.生成一个监听的socket,lfd
    int lfd = Socket(AF_INET,SOCK_STREAM,0);

    //两个队列的数量的和的最大值
    int backlog = 128;
    //ip地址
    string ip = "192.168.123.18";

    //监听ip地址的结构体，等一下要和socket相关联(bind)
    struct sockaddr_in s_sddr;
    s_sddr.sin_port=htons(9000);
    s_sddr.sin_family=AF_INET;
    inet_pton(AF_INET,ip.data(),&s_sddr.sin_addr.s_addr);
    
    //tcpbind链接，监听lfd，设置为非阻塞,
    int flag = fcntl(lfd,F_GETFL,0);
    fcntl(lfd,F_SETFL,flag|O_NONBLOCK);

    Bind(lfd,(struct sockaddr *)&s_sddr,sizeof(s_sddr));
    //epoll上树,设置lfd上树以及事件类型
    struct epoll_event ev;
    memset(&ev,0,sizeof(ev));
    ev.data.fd=lfd;
    ev.events=EPOLLIN|EPOLLET;//设置读事件和边沿触发
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

    Listen(lfd,128);

    cout<<"one"<<endl;
    //定义Pth
    Pth pth(&taskl);
    //生成线程
    pthread_t tid;
    pthread_create(&tid,NULL,doMpth,&pth);
    pthread_detach(tid);
    
    for(int i = 0; i<3;i++)
    {
        pthread_t tid;
        pthread_create(&tid,NULL,dopth,&pth);
        pthread_detach(tid);
        
    }
    pth.set_pnum(3);
    
    
    //while循环,epoll_wait
    //lfd,accept
    //增加cfd的epoll_event到树上里面
    //
    //将接受到的epollevet到tasklist上
    //
    while(true)
    {
        cout<<"first while"<<endl;
        //等待有消息进来
        int ret = Epoll_wait(epfd,evs,EVENTLEN,-1);
        if(-1 == ret)continue;

        //循环event列表
        for(int i =0 ;i<ret;++i)
        {
            cout<<"get num :"<<ret<<endl;
            //是监听fd的并且是读事件
            if(lfd == evs[i].data.fd &&evs[i].events&EPOLLIN )
            {
                while(true){
                   
                    Task *trecord = new Task();//用来暂时保存事件的数据
                    struct sockaddr_in srecord;//暂时用来保存客户的信息
                    socklen_t slen= sizeof(struct sockaddr_in);
                    int ret = Accept(lfd,(struct sockaddr *)&srecord,&slen);
                    if(-1 == ret )break;

                    int flag = fcntl(ret,F_GETFL);
                    fcntl(ret,F_SETFL,flag|O_NONBLOCK);
                  
                    //将该事件转为任务,加入任务数组和上树
                    trecord->set_fun(print);//传入task将要的执行函数
                    
                   
                    //设置新的监听事件
                    struct epoll_event ev;
                    memset(&ev,0,sizeof(ev));
                   
                    ev.events=EPOLLIN|EPOLLET;//设置读事件和边沿触发
                    cout<<"trecord"<<endl;
                    trecord->set_fd(ret);
                    trecord->set_event(ev.events);
                    ev.data.ptr = trecord;
                    //让event指向task,
                    //这里ptr有问题，一旦写了这一句代码，read就会一直处于
                    //-1的返回结果,原因是epoll_data是union
                    epoll_ctl(epfd,EPOLL_CTL_ADD,ret,&ev);
                    
                    
                }
            }
            //判断evs[i]发生的事件和设置在相关task里面的是否相同
            //else if(evs[i].events & ((Task*)(evs[i].data.ptr))->get_event())
            else if(evs[i].events & EPOLLIN)
            {
                cout<<"in"<<endl;
                /*这里实际要实现的是加入TaskList*/

                //////////////////////////////////
                Task *tt =(Task *)evs[i].data.ptr;
                //
                taskl.push_back(&evs[i]);
                /*
                //
                int cfd =tt->get_fd();
                char buf[1024];
                int ret = read(cfd,buf,1024);
                if(ret >0 ){
                    
                    tt->set_buf(buf);
                    tt->do_fun();
                    write(cfd,buf,ret);
                }
                else if(0 == ret )
                {
                    cout<<"connection close"<<endl;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
                    close(evs[i].data.fd);                   
                }
                else{
                    cout<<"kkk:"<<ret<<endl;
                    
                }
                */              
            }
        }
    }
   

    //结束，释放空间
    
    return 0;
}
