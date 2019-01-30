#ifndef __UDP_SOCKET_HPP__
#define __UDP_SOCKET_HPP__

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<assert.h>
using namespace std;

typedef  struct sockaddr sockaddr;
typedef  struct sockaddr_in sockaddr_in;


class UdpSocket
{
  public:
    UdpSocket()
      :_fd(-1)
    {}

    //创建套接字
    bool Socket()
    {
      _fd = socket(AF_INET,SOCK_DGRAM,0);
      if(_fd < 0){
        perror("use socket");
        return false;
      }
      return true;
    }

    //关闭套接字，就是关闭文件描述符
    bool Close()
    {
      close(_fd);
      return true;
    }

    //绑定端口号
   // bool Bind(const string& ip,uint16_t port)
   bool Bind(uint16_t port)
    {
      sockaddr_in addr;//IPv4的地址类型
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);//主机字节序转网络字节序
     // addr.sin_addr.s_addr = inet_addr(ip.c_str());//inet_addr可以将字符串转为IP地址
     addr.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY代表0.0.0.0
      int ret = bind(_fd,(sockaddr*)&addr,sizeof(addr));
      if(ret < 0 )
      {
        perror("use bind");
        return false;
      }
      return true;
    }

    //接受消息
    bool RecvFrom(string* buf,string* ip = NULL,uint16_t* port = NULL)
    {
      char tmp[1024] = {0};
      sockaddr_in addr;
      socklen_t len = sizeof(addr);
      //返回值为实际接受到的字符个数
      ssize_t rs = recvfrom(_fd,tmp,sizeof(tmp)-1,0,(sockaddr*)&addr,&len); 
       if(rs < 0)
       {
         perror("use recefrom");
         return false;
       }
       //assign是使用c类指针tmp的前rs个字符重新复制buf
       buf->assign(tmp,rs);

       //如果外部要使用addr中的ip地址和端口号，则赋值，否则直接跳过
       if(ip!=NULL)
       {
         *ip = inet_ntoa(addr.sin_addr);
       }

       if(port != NULL)
       {
         *port = ntohs(addr.sin_port);
       }
    
       return true;
    }


    //发送消息
    bool SendTo(const string& buf,const string& ip,uint16_t  port)
    {
      sockaddr_in addr;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      addr.sin_port = htons(port);
      addr.sin_family = AF_INET;

      ssize_t ws = sendto(_fd, (void*)buf.c_str(), buf.size(), 0, (sockaddr*)&addr, sizeof(addr));
         if(ws < 0)
         {
                perror("use sendto");
                     return false;
                        
         }
            return true;
              
    }
  private:
    int _fd;
};



#endif 
