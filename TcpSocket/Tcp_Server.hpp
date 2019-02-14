#pragma once 

#include"Tcp_Socket.hpp"

typedef void(*Handler)(string& req,string* res);

class TcpServer
{
  public:
    TcpServer(string ip,uint16_t port)
      :_ip(ip)
      ,_port(port)
    {}
   
    void Start(Handler handler)
    {
      //1.创建socket
      listen_sock.Socket();
      //2.绑定ip与端口号
      listen_sock.Bind(_ip,_port);
      //3.监听
      listen_sock.Listen(5);

      while(1)
      {
        TcpSocket new_sock;
        string ip;
        uint16_t port;
        //4.接受连接
        listen_sock.Accept(&new_sock,&ip,&port);
        cout<<"client:"<<ip.c_str()<<" connect"<<endl;
        while(1)
        {
          //5.连接成功读取客户端请求
          string req;
          new_sock.Recv(&req);
          //6.处理请求
          string res;
          handler(req,&res);

          //写回处理结果
          new_sock.Send(res);
          cout<<"client:"<<ip.c_str()<<"REQ:"<<req<<".RES:"<<res<<endl;
        }
      }
    }

  private:
    TcpSocket listen_sock;
    string _ip;
    uint16_t _port;
};
