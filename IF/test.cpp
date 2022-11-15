#include<iostream>
#include<string>
#include<iomanip>
#include<cstring>
#include<arpa/inet.h>
#include"IF.h"

using std::cout;using std::cin;using std::endl;
using std::string;
int main(int argc,char** argv)
{
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
    cout<<std::setbase(10);

    delete(interface);

    return 0;
}
