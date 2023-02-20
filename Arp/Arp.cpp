#include"Arp.h"


/*setter*/
inline void Arp::set_opt(short io)
{
    opt=op;
}
inline void Arp::set_srmac(const char *sm)
{
    memcpy(srcmac,sm,MACLEN);
}

inline void Arp::set_srcip(const char *sip)
{
    memcpy(srcip,sip,IPLEN);
}
inline void Arp::set_dstmac(const char *dm)
{
    memcpy(dstmac,dm,MACLEN);
}
inline void Arp::set_dstip(const char *dip)
{
    memcpy(dstip,ddip,IPLEN);
}

/*getter*/

inline const short & Arp::get_opt()
{
    return opt;
}
inline const unsigned char *Arp::get_srcmac()
{
    return srcmac;
}
inline const unsigned char *Arp::get_srcip()
{
    return srcip;
}
inline const unsigned char *Arp::get_dstmac()
{
    return dstmac;
}
inline const unsigned char *Arp::get_dstip()
{
    return dstip;
}


void Arp::create_arp(char *buf)
{
    short tmp=htons(hardType);
    char *temp=(char*)(&tmp);
    memcpy(buf,temp,2);

    temp=htons(proType);
    char *temp=(char*)&tmp;
    memcpy(buf+2,temp,2);

    memcpy(buf+4,&hardLen,1);
    memcpy(buf+5,&proLen,1);

    temp=htons(opt);
    char *temp=(char*)&tmp;
    memcpy(buf+6,temp,2);

    int local=8;
    memcpy(buf+local,srcmac,MACLEN);
    local+=MACLEN;
    memcpy(buf+local,srcip,IPLEN);
    local+=IPLEN;
    memcpy(buf+local,dstmac,MACLEN);
    local+=MACLEN;
    memcpy(buf+local,dstip,IPLEN);
}


void Arp::analy_arp(const char *buf)
{
    char *temp;

    memcpy();
}


