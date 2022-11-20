#include<iostream>
#include<string>
#include<cstring>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iomanip>

#include"Ip_dg.h"
using std::cout;using std::cin;using std::endl;

int main(int argc,char** argv)
{
    //ip要发送的数据
    char * msg={"abcdefghijklmn"};
    size_t len = strlen(msg);

    //将字符串的ip变为in_add_t类型的
    in_addr_t src,dst;
    src = inet_addr("192.168.3.38");
    dst = inet_addr("192.168.3.1");

    //生成的ip
    Ip_dg *ipdg = new Ip_dg();
    ipdg->create_ip(0x45,0,len+20,-1,nullptr,0x80,0x06,&src,&dst,msg,len);
    const unsigned char * buf = ipdg->get_buf();
    cout<<std::setbase(16)<<std::setfill('0');
    for(size_t i =0;i<len+20;++i){
        cout<<static_cast<unsigned>(buf[i])<<':';
    }
    cout<<std::setbase(10)<<endl;

    delete(ipdg);

}
