#include<iostream>
#include<string>
#include<iomanip>
#include<cstring>
#include<arpa/inet.h>
#include"IF.h"
#include"mac_datagram.h"

using std::cout;using std::cin;using std::endl;
using std::string;
int main(int argc,char** argv)
{
    //测试IF
    IF *interface = new IF;
    string ip{"192.168.10.1"};
    cout<<"ip 修改为"<<ip<<endl;
    interface->set_ip(ip.c_str());

    unsigned char temp[MACLEN]={0x02,0x05,0x7e,0x8f,0x5a,0xcd};
    interface->set_mac(temp);

    struct sockaddr_in sin = interface->get_ifaddr();
    unsigned char * mac = interface->get_mac();

    cout<<std::setbase(16)<<std::setfill('0');
    for(size_t i = 0; i<MACLEN;i++){
        cout<<static_cast<unsigned>(mac[i])<<":";
    }
    cout<<endl;
    char *c_ip = inet_ntoa(sin.sin_addr);
    cout<<c_ip<<endl;

    //cout<<std::setbase(10);

    //生成mac报文
    Mac_dg mdg;
    mdg.set_dstmac(temp);
    mdg.set_srcmac(temp);
    mdg.set_type(0x0800);

    string mac_msg{"abcdefgabjklAB"};
    size_t rlen = 16+mac_msg.length();
    const unsigned char *y;
    y = mdg.create_mac(mac_msg.data(),mac_msg.length());

    unsigned char yy[rlen];
    memcpy(yy,y,rlen);

    mdg.analy_mac((const char *)yy,rlen);
    const unsigned char * kk = mdg.get_buf();
    for(size_t i = 0;i<strlen((const char *)kk);++i)
        cout<<static_cast<unsigned>(kk[i])<<':';
    cout<<endl;
    const unsigned char *t = mdg.get_dstmac();
    for(size_t i =0;i<6;++i)
    {
        cout<<static_cast<unsigned>(t[i])<<':';
    }
    cout<<endl;
    t = mdg.get_srcmac();
    for(size_t i =0;i<6;++i)
    {
        cout<<static_cast<unsigned>(t[i])<<':';
    }
    cout<<endl;
    const short ss =mdg.get_type();
    cout<<ss<<endl;

    
    cout<<std::setbase(10);
    delete(interface);

    return 0;
}
