
#include"Ip_dg.h"

Ip_dg::~Ip_dg(){
    delete(buf);
}

//下面的参数分别是:【版本和首部长度】、【区分服务】、【总长度】、
//【标识】、【标志与片偏移】、【生存时间】、【上层协议】、
//【源地址】、【目的地址】、【数据】
//最前面的两个参数可以为NULL,ttl,identification,flag,offset
//也可以不写，直接使用自己生成的
const unsigned  char *Ip_dg::create_ip(const  char avl,
        const char atos,const short atotlen,
        const short aidentity,const void *asao,
        const char attl,const char apro,
        const void *src,const void *dst,
        const void *msg,const size_t dglen)
{
    //buf申请空间
    if(nullptr != buf){
        delete(buf);
    }
    buf = new unsigned char[atotlen];

    //专门用来存放short转为char*的数据的变量
    char *temp{nullptr};

    if(0 == avl) buf[0] =v;
    else buf[0] = avl;
    if(0 == atos) buf[1] = tos;
    else buf[1] = atos;

    //atotlen变为char*，然后mencpy
    temp = stochptr(temp,atotlen);
    memcpy(buf+2,temp,2);

    if( aidentity < 0) 
    {
        //identification变为char*，然后mencpy
        temp = stochptr(temp,identification);
        memcpy(buf+4,temp,2);
    }
    else
    {
        //identity变为char*，然后mencpy
        temp = stochptr(temp,aidentity);
        memcpy(buf+4,temp,2);
    }
    if(nullptr == asao)
    {
        memcpy(buf+6,sign_and_offset,2);
    }
    else
    {
        //标志与片偏移
        memcpy(buf+6,asao,2);
    }
    char cks[2]{'\0','\0'};


    //生存时间，协议
    buf[8]=attl;buf[9]=apro;

    //首部校验和
    memcpy(buf+10,cks,2);

    //源IP，目的ip
    memcpy(buf+12,src,IPLEN);
    memcpy(buf+16,dst,IPLEN);

    //上层的信息
    memcpy(buf+20,msg,dglen);

    //计算校验和，然后写入ip段中
    short cs = crc((unsigned short*)buf,(size_t)(buf[0]&0x0f)*4);
    char *checks = (char *)&cs;
    memcpy(buf+10,checks,2);

    return buf;
}

/*解析受到的IP报文*/
int Ip_dg::analy_ip(const char *msg,size_t dglen)
{
    v = msg[0];
    short cs = crc((unsigned short *)msg,(size_t)(v&0x0f)*4);
    if( 0 != cs)
    {
        std::cout<<"校验和出错"<<std::endl;
        return -1;
    }
    //写入v,tos
    tos = msg[1];
    //得到totlen
    totlen=chptrtos(msg+2);

    //得到identification
    identification = chptrtos(msg+4);

    //得到标志与片偏移
    memcpy(sign_and_offset,msg+6,2);

    //得到ttl(生存时间),protocol(上层使用的协议)
    ttl = msg[8];
    protocol = msg[9];

    //不用管checksum,直接将数据写入buf
    //计算首部长度
    size_t yl=(size_t)(v&0x0f)*4;
    if(nullptr != buf)
    {
        delete(buf);
    }
    buf = new unsigned char[dglen-yl];
    memcpy(buf,msg+yl,dglen-yl);

}

//getter

const unsigned char *Ip_dg::get_buf()
{
    return buf;
}
const unsigned char Ip_dg::get_v()
{
    return v;
}
const unsigned char Ip_dg::get_atos()
{
    return atos;
}
const unsigned char *Ip_dg::get_src()
{
    return src_ip;
}
const unsigned char *Ip_dg::get_dst()
{
    return dst_ip;
}
const short Ip_dg::get_totlen()
{
    return totlen;
}
const short Ip_dg::get_identification()
{
    return identification;
}
const unsigned char *Ip_dg::get_sign_and_offset()
{
    return sign_and_offset;
}
const unsigned char Ip_dg::get_ttl()
{
    return ttl;
}
const unsigned char Ip_dg::get_protocol()
{
    return protocol;
}
