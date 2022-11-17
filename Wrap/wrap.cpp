#include"wrap.h"
#include<sys/socket.h>
#include<unistd.h>
#include<sys/epoll.h>
int Bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen){
    int ret = bind(sockfd,addr,addrlen);
    if(-1 == ret){
        perror("bind:");
        exit(1);
    }
    return ret;
}
int tcp4Bind(const short port,const char *ip){
    int sockfd = Socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(nullptr == ip)
    {
        addr.sin_addr.s_addr =INADDR_ANY;
    }
    else{
    inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);
    }
    int res = Bind(sockfd,&addr,sizeof(addr));
    return sockfd;
}
int Accept(int sockfd,struct sockaddr* addr,socklen_t *addrlen){
    int ret = accept(sockfd,addr,addrlen);
    if(-1 == ret){
        if(EAGAIN == errno || EINTR == errno)
            continue;
        perror("accept:");
        exit(1);
    }
    struct sockaddr_in *temp = (struct sockaddr_in *)addr;
    printf("client:ip=%s , port=%d\n",
            inet_ntoa(temp->sin_addr),ntohs(temp->sin_port));

}
int Socket(int daemon,int type,int protocol){
    int ret = socket(daemon,type,protocol);
    if(-1 == ret){
        perror("socket:");
        exit(1);
    }
    return ret;
}
int Connect(int sockfd,struct sockaddr *addr,socklen_t len){
    int ret = connect(sockfd,addr,len);
    if(-1 == ret){
        perror("connect:");
        exit(1);
    }
    return ret;
}
int Listen(int sockfd,int backlog){
    int ret = listen(sockfd,backlog);
    if(-1 == ret){
        perror("listen:");
        exit(1);
    }
    return ret;
}
int Write(int fd,const void  *buf,size_t count){
    int ret = write(fd,buf,count);
    if(-1 == ret){
        perror("write:");
        exit(1);
    }
    return ret;
}
int Read(int fd,void *buf,size_t count){
    int ret = read(fd,buf,count);
    if(-1 == ret){
        perror("read:");
        exit(1);
    }
    return ret;
}

int Epoll_create(size_t n)
{
    int res = epoll_create(n);
    if(-1 == res)
    {
        perror("Epoll_create:");
        exit(1);
    }
    return res;
}
int Epoll_wait(int epfd,epoll_event *evs,int maxevents,int timeout)
{
    int res = epoll_wait(epfd,evs,maxevents,timeout);
    if(-1 == res)
    {
        if(EINTR != errno)
        {
            perror("Epoll_wait:");
            exit(1);
        }
    }
    return res;
}
