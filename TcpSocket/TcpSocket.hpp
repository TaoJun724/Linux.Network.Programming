#ifndef __TCPSOCKET_HPP__
#define __TCPSOCKET_HPP__ 


#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<iostream>
#include<string>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
using namespace std;

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

class TcpSock{
     private:
       int fd_;

     public:
       TcpSock():fd_(-1)
         {}
       TcpSock(int fd):fd_(fd)
         {}

       bool Socket()
       {
          fd_ = socket(AF_INET,SOCK_STREAM,0);
          if(fd_ < 0)
          {
            cerr<<"socket eror!"<<endl;
            return false;
          }
          cout<<"open fd ="<<fd_<<endl;
          return true;
       }
            
       bool Close()const 
       {
         close(fd_);
         cout<<"close fd ="<<fd_<<endl;
         return true;
       }

       bool Bind(const string& ip,uint16_t port)const 
       {
         sockaddr_in addr;
         addr.sin_family = AF_INET;
         addr.sin_port = htons(port);
         addr.sin_addr.s_addr = inet_addr(ip.c_str());

         if(bind(fd_,(sockaddr*)&addr,sizeof(addr))<0)
         {
           cerr<<"bind error!"<<endl;
           return false;
         }
         return true;
       }

       bool Listen(int num)const
       {
         if(listen(fd_,num) < 0)
         {
           cerr<<"listen error"<<endl;
           return false;
         }
         return true;
       }

       bool Accept(TcpSock* peer,string* ip = nullptr,uint16_t* port = nullptr)const 
       {
         sockaddr_in peer_addr;
         socklen_t len = sizeof(peer_addr);
         int sock = accept(sock,(sockaddr*)&peer_addr,&len);
         if(sock<0)
         {
           cerr<<"accept error"<<endl;
           return false;
         }
        cout<<"accept fd = %d\n"<<sock<<endl;

        peer->fd_=sock;
        if(ip!=nullptr)
        {
          *ip = inet_ntoa(peer_addr.sin_addr);
        }
        if(port!=nullptr)
        {
          *port = ntohs(peer_addr.sin_port);
        }
        return true;
       }




       bool Recv(std::string* buf) const
       {
         buf->clear();
         char tmp[1024 * 10] = {0};
          // [注意!] 这里的读并不算很严谨, 因为一次 recv 并不能保证把所有的数据都全部读完
         // 参考 man 手册 MSG_WAITALL 节.
         ssize_t read_size = recv(fd_, tmp, sizeof(tmp), 0);
         if (read_size < 0)
         {
           perror("recv");
           return false;
         }
         if (read_size == 0)
         {
            return false;
         }
         buf->assign(tmp, read_size);
         return true;
       }

  bool Send(const std::string& buf) const {
     ssize_t write_size = send(fd_, buf.data(), buf.size(), 0);
     if (write_size < 0) {
        perror("send");
         return false;
        
    }
     return true;
     
  }
 

  bool Connect(const std::string& ip, uint16_t port) const {
     sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        int ret = connect(fd_, (sockaddr*)&addr, sizeof(addr));
        if (ret < 0) {
            perror("connect");
            return false;
            
         }
         return true;
         
  }
  
  int GetFd()const 
 {
   return fd_; 
 }
};


#endif 
