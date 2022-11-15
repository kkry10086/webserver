#include"IF.h"
#include<iostream>
#include<string>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<cstring>
#include<arpa/inet.h>
#include<unistd.h>
#include<net/if.h>


IF::IF(){
    //sock初始化
    sock = socket(AF_INET,SOCK_STREAM,0);
    //ifreq.ifr_name也赋值
    memcpy(&ifr.ifr_name,ETHNAME,IFNAMSIZ); 
    set_ip();
    set_mac(); 
}
IF::~IF(){
    close(sock);
}

void IF::set_mac()
{
    int ret = ioctl(sock,SIOCGIFHWADDR,&ifr);
    if(-1 == ret){
        perror("ioctl in set_mac ");
        exit(0);
    }
    memcpy(mac,ifr.ifr_hwaddr.sa_data,MACLEN);
}
//根据macp修改mac的数据
void IF::set_mac(const unsigned char *macp){
    memcpy(mac,macp,MACLEN);
}
void IF::set_ip()
{
    int ret = ioctl(sock,SIOCGIFADDR,&ifr);
    if( -1 == ret){
        perror("ioctl in set_ip ");
        exit(0);
    }
    memcpy(&ifaddr,&ifr.ifr_addr,sizeof(ifaddr));
}
//根据ipp修改sockaddr_in的ip数据
void IF::set_ip(const char * ipp){
    int ret = inet_pton(AF_INET,ipp,&ifaddr.sin_addr.s_addr);
    if(0 == ret){
        std::cout<<"src ip address is invalid"<<std::endl;
        exit(1);
    }
    else if(-1 == ret){
        perror("inet_pton:");
        exit(1);
    }
}
//获取mac数据
unsigned char * IF::get_mac()
{
    return mac;
}
//获取ifaddr的数据
struct sockaddr_in& IF::get_ifaddr()
{
    return ifaddr;
}


