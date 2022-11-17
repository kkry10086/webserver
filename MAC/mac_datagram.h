
#ifndef __MAC_DATAGRAM_H
#define __MAC_DATAGRAM_H
#include<string>
#include<cstring>
#include<arpa/inet.h>
#include<iostream>

#define MACLEN 6

class Mac_dg
{
    private:
        unsigned char dst_mac[MACLEN];
        unsigned char src_mac[MACLEN];
        short ptype;
        unsigned char *buf = nullptr; 

    public:
        ~Mac_dg();

        //setter
        void set_dstmac(const unsigned char *);
        void set_srcmac(const unsigned char *);
        void set_type(const short&);

        //getter
        const unsigned char* get_dstmac();
        const unsigned char* get_srcmac();
        const unsigned char *get_buf();
        const short& get_type();

        //create_mac_datagram
        const unsigned char * create_mac(const char *,size_t );

        //分析mac_datagram
        const unsigned char * analy_mac(const char *,size_t);

        //校验和
        short crc(unsigned short *buf,size_t len);
            
};



#endif
