#ifndef __IF_H
#define __IF_H
#include<net/if.h>
#define ETHNAME "eth0"
#define MACLEN 6
#define IPLEN 4
class IF
{
    private:
        struct ifreq ifr;
        //usr/include/net/if.h
        int sock = 0;
        unsigned char mac[MACLEN];
        unsigned char ip[IPLEN];
    public:
        IF();
        ~IF();
        void set_mac();
        void set_ip();
        unsigned char *get_ip();
        unsigned char *get_mac();
};

#endif
