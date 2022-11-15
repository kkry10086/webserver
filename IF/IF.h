#ifndef __IF_H
#define __IF_H
#include<arpa/inet.h>
#include<net/if.h>
#define ETHNAME "wlp4s0"
#define MACLEN 6
#define IPLEN 4
class IF
{
    private:
        struct ifreq ifr;
        //usr/include/net/if.h
        int sock = 0;
        unsigned char mac[MACLEN];
        struct sockaddr_in ifaddr;
    public:
        IF();
        ~IF();
        void set_mac();
        //根据参数修改mac
        void set_mac(const unsigned char *);
        void set_ip();
        //根据参数修改ifaddr
        void set_ip(const char *);
        //获取ifaddr
        struct sockaddr_in& get_ifaddr();
        //获取mac
        unsigned char *get_mac();
};

#endif
