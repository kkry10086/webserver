#ifndef ARP_H
#define ARP_h


#include<iostream>
#include<cstring>
#include<unistd.h>
#include<arpa/inet.h>

class Arp
{
private:
    short hardType{1};//硬件类型
    short proType{0x0800};//协议类型

    unsigned char hardLen{0x06};//硬件地址长度
    unsigned char proLen{0x04};//协议地址长度

    short opt;//操作类型

    unsigned char srcmac[MACLEN];
    unsigned char srcip[IPLEN];

    unsigned char dstmac[MACLEN]('0xff',6);
    unsigned char dstip[IPLEN];
public:
    //构造函数
    //Arp();
    //setter
    void set_opt(short op);
    void set_srcmac(const char *sm);
    void set_srcip(const char *sip);
    void set_dstmac(const char *dm);
    void set_dstip(const char *dip);

    //getter
    const short &get_opt();
    const unsigned char *get_srcmac();
    const unsigned char *get_srcip();
    const unsigned char *get_dstmac();
    const unsigned char *get_dstip();


    /*创建Arp的函数,buf是要生成的arp的数据存放 
      的地点*/
    void create_arp(char *buf);

    /*解析arp的函数*/
    void analy_arp(const char *buf);
};



#endif
