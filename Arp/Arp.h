#include<iostream>
#include<string>
#include<unistd.h>

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
    
};
