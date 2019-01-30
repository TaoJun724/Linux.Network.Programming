#ifndef __UDP_SERVER_HPP__
#define __UDP_SERVER_HPP__
#include"Udp_Socket.hpp"

typedef void (*Handler)(const string& req,string* res);

class UdpServer{
 public:
   UdpServer()
   {
     //创建套接字
     assert(sock_.Socket());
   }

   ~UdpServer(){
     sock_.Close();
   }

  // bool Start(const string& ip,uint16_t  port,Handler handler)
  bool Start(uint16_t port,Handler handler)
   {
     //创建socket
     //绑定端口号
     //进入事件循环
     //尝试读取请求
     //根据请求计算响应
     //根据响应给客户端
     
     bool ret = sock_.Bind(port);
     if(!ret)
     {
       return false;
     }

     while(1){
       string req;
       string remote_ip;
       uint16_t  remote_port = 0;
       bool ret = sock_.RecvFrom(&req,&remote_ip,&remote_port);

       if(!ret)
       {
         continue;
       }


       string res;
       handler(req,&res);

       sock_.SendTo(res,remote_ip,remote_port);
       printf("[%s:%d] req: %s,resp:%s\n",remote_ip.c_str(),remote_port,req.c_str(),res.c_str());
     }
       sock_.Close();
       return true;
   }
 private:
   UdpSocket sock_;
};





#endif
