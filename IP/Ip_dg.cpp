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
        const short aidentity,const char *asao,
        const char attl,const char apro,
        const char *src,const char *dst,
        const char *msg)
{
    std::string res{0};
    std::cout<<"reslen:"<<res.length()<<std::endl;
    if(NULL == avl)avl =vl;
    if(nullptr == atos)atos =tos;
    if(nullptr == aidentity) aidentity= identification;
    if(nullptr == asao) asao = sign_and_offset;
    char cks[2]={'\0','\0'};

   //将short类型转为char*
   short temp;
   temp =htons(atotlen);
   char *total_len = (char *)&temp;
   temp = htons(aidentity);
   char *iden = (char *)&temp;
    res=res+avl+atos+total_len+iden+asao+attl+apro+cks+src+dst+msg;
    std::cout<<res<<std::endl;
    

}
