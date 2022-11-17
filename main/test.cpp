#include<iostream>
#include<string>
#include<sys/epoll.h>
#include<fcntl.h>
#include<unistd.h>
#include"wrap.h"

using std::cout;using std::cin;using std::endl;
int main(int argc,char** argv)
{
    int lfd = tcp4Bind(8090,NULL);
    Listen(fd,128);
    int epfd = Epoll_create(1);
    
    struct epoll_event ev,evs[1024];
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);
    while(1){
        int nready = Epoll_wait(epfd,evs,1024,-1);
            
        for(int i =0;i<nready;++i){
                if(evs[i].events&EPOLLIN && evs[i].data.fd==lfd){
                }
                else if()
                {
                }
            }
        }
    }


    return 0;
}
