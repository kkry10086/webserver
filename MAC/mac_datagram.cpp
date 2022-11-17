#include"mac_datagram.h"

//析构函数
Mac_dg::~Mac_dg(){
    delete(buf);
    buf = nullptr;
}

void Mac_dg::set_dstmac(const unsigned char * dst)
{
    memcpy(dst_mac,dst,MACLEN);
}

void Mac_dg::set_srcmac(const  unsigned char *src)
{
    memcpy(src_mac,src,MACLEN);
}
void Mac_dg::set_type(const short& t)
{
    ptype = t;
}

const unsigned char * Mac_dg::get_dstmac()
{
    return dst_mac;
}
const unsigned char * Mac_dg::get_srcmac()
{
    return src_mac;
}
const short& Mac_dg::get_type()
{
    return ptype;
}
const unsigned  char * Mac_dg::get_buf()
{
    return buf;
}
//校验和,这里要求sum的数据中可能大于16位的数据变为零，但是必须通过算法的加
//减实现。因此要与低16位进行计算，直到前面16位为0。
//所以在实现上要将前面16位的数据通过算法变为0,
//在这里都是short的计算。所以前后顺序可以改变。除了最后两步。
short Mac_dg::crc(unsigned  short *buf,size_t len){
    unsigned int sum{0};
    size_t rlen = len/2;
    for(size_t i =0;i!=rlen;++i){
        sum+=*buf;
        buf++;
    }
    sum = (sum>>16)+(sum&0xffff);
    sum += (sum>>16);
    return ~sum;

}

//create_mac_datagr
const unsigned char *  Mac_dg::create_mac(const char *msg,size_t len)
{
    //总的mac的长度
    size_t maclen = len+16;
    //unsigned char buf[maclen];
    if(nullptr != buf){
        delete(buf);
    }
    buf = new unsigned char[maclen];
    short temp = htons(ptype);
    unsigned char *h = (unsigned char *)&temp; 
    memcpy(buf,dst_mac,MACLEN);
    memcpy(buf+6,src_mac,MACLEN);
    memcpy(buf+12,h,2);
    memcpy(buf+14,msg,len);
    short macrc = crc((unsigned short*)buf,maclen-2);
    //short nmacrc = htons(macrc);
    unsigned char * mc = (unsigned char *)&(macrc);
    memcpy(buf+maclen-2,mc,2);

    return buf;
}

const unsigned char *Mac_dg::analy_mac(const char *amsg,size_t len)
{
    short macrc = crc((unsigned short *)msg,len);
    if(0x0000 != macrc ){
        std::cout<<"校验和结果错误"<<macrc<<std::endl;
        return nullptr;
    }
    memcpy(dst_mac,msg,MACLEN);
    memcpy(src_mac,msg+6,MACLEN);
    unsigned char temp[2];
    memcpy(temp,msg+12,2);
    ptype =ntohs (*(short *)temp);

    //获得mac中的数据
    size_t reslen = len-16;
    //unsigned char res[reslen];
    if(nullptr != buf){
        delete(buf);
    }
    buf = new unsigned char[reslen+1];
    memset(buf,0,reslen+1);
    //这里memcpy一直把前两个字符修改了,因为我使用了buf(msg)作为
    //传入的数据，又在前面delete，自然就没有了对该空间的保护。
    memcpy(buf,msg+14,reslen);
    buf[reslen]='\0';
    return buf;
}
