#pragma once 


#include<arpa/inet.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string>
#include<stdlib.h>
#include<netinet/in.h>
#include<fcntl.h>


using namespace std;

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;


class TcpSocket
{
  public:
    TcpSocket(){}

    TcpSocket(int fd)
    {
      _fd = fd;
    }

    //创建套接字
    void Socket()
    {
      _fd = socket(AF_INET,SOCK_STREAM,0);
      if(_fd < 0)
      {
        perror("use socket");
        return ;
      }
    }

    //关闭套接字
    void Close() const 
    {
      close(_fd);
    }

    //绑定ip与端口号
    void Bind(const string& ip,uint16_t port)
    {
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      addr.sin_port = htons(port);
      if(bind(_fd,(sockaddr*)&addr,sizeof(addr))<0)
      {
        perror("use bind");
        return ;
      }
    }

    //监听
    void Listen(int backlog)
    {
      if(listen(_fd,backlog)<0)
      {
        perror("use listen");
        return ;
      }
    }

    //服务器接受连接
    void Accept(TcpSocket* obj,string* ip = NULL,uint16_t* port = NULL)
    {
      sockaddr_in peer;
      socklen_t len = sizeof(peer);
      int new_sock = accept(_fd, (sockaddr*)&peer, &len);
      if(new_sock < 0){
        perror("use accept");
        return;
      }
      obj->_fd = new_sock;

       if(ip != NULL)
       {
         *ip = inet_ntoa(peer.sin_addr);           
       }
       if(port != NULL)
       {
         *port = ntohs(peer.sin_port);           
       }
    }

    //接受消息
    void Recv(string* buf)
    {
       buf->clear();
       char peer[1024];
       ssize_t read_size = read(_fd, peer, sizeof(peer) - 1); 
       if(read_size < 0){
           perror("use read");
           return;                     
       }
      buf->assign(peer, read_size);
    }

    //发送消息
    void Send(const string& buf)
    {
        ssize_t write_size = write(_fd, buf.c_str(), buf.size());
        if(write_size < 0){
           perror("use wirte");
           return;           
        }
    }
   
    //客户端建立连接
    void Connect(string& ip,uint16_t port)
    {
      sockaddr_in addr;
       addr.sin_family = AF_INET;
       addr.sin_addr.s_addr = inet_addr(ip.c_str());
       addr.sin_port = htons(port);

       if(connect(_fd, (sockaddr*)&addr, sizeof(addr)) < 0)
       {
         perror("use connect");
         return;
       }
    }

    int  Getfd()const{
      return _fd;
    }
   

  private:
    int _fd = -1;
};
