#include"IF.h"
#include<iostream>
#include<string>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<cstring>
#include<arpa/inet.h>
#include<unistd.h>
#include<net/if.h>

#define ETHNAME "eth0"
#define MACLEN 6
#define IPLEN 4
using std::cout;using std::cin;using std::endl;

IF::IF(){
    //sock初始化
    sock = socket(AF_INET,SOCK_STREAM,0);
    //ifreq.ifr_name也赋值
    memcpy(&ifr.ifr_name,ETHNAME,IFNAMSIZ);  
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
void IF::set_ip()
{
    int ret = ioctl(sock,SIOCGIFADDR,&ifr);
    if( -1 == ret){
        perror("ioctl in set_ip ");
        exit(0);
    }
    memcpy(ip,ifr.ifr_addr.sa_data,IPLEN);
}
unsigned char * IF::get_mac()
{
    return mac;
}
unsigned char * IF::get_ip()
{
    return ip;
}


