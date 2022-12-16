#ifndef __IP_DG_H
#define __IP_DG_H

#include<string>
#include<iostream>
#include<arpa/inet.h>
#include<cstring>
#include<sys/epoll.h>
#include"wrap.h"

#define IPLEN 6

class Ip_dg
   {
   private:
       unsigned char v{0x45};//版本与首部长度
       unsigned char tos{0};//区分服务
       unsigned char *src_ip;//源ip
       unsigned char *dst_ip;//目的ip
       short totlen;//总长度
       short identification{0};//标识
       unsigned char sign_and_offset[2]{0};//标志与片偏移
       unsigned char ttl{0x80};//生存时间
       unsigned char protocol;//上一层的协议
       //short checksum;//首部校验和
       unsigned char *buf;//数据

   public:
       ~Ip_dg();
       const unsigned  char *create_ip(const char avl,
                 const char atos,const short atotlen,
                 const short aidentity,const void *asao,
                 const char attl,const char apro,
                 const void *src,const void *dst,
                 const void *msg,const size_t dglen);

       //上面的参数分别是:【版本和首部长度】、【区分服务】、【总长度】、
       //【标识】、【标志与片偏移】、【生存时间】、【上层协议】、
       //【源地址】、【目的地址】、【数据】
       //最前面的两个参数可以为NULL,ttl,identification,flag,offset
       //也可以不写，直接使用自己生成的

       //ip解析函数
       int analy_ip(const char *msg,size_t dglen);

       //getter
       const unsigned char * get_buf();
       const unsigned char get_v();
       const unsigned char get_tos();
       const unsigned char *get_src();
       const unsigned char *get_dst();
       const short get_totlen();
       const short get_identification();
       const unsigned char *get_sign_and_offset();
       const unsigned char get_ttl();
       const unsigned char get_protocol();

       

};

#endif
