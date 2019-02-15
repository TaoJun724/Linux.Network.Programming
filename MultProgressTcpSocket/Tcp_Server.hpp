#pragma once 

#include"Tcp_Socket.hpp"
#include<functional>
#include<signal.h>


typedef void(*Handler)(string& req,string* res);

class TcpServer 
{
  public:
    TcpServer(string& ip,uint16_t port)
      :_ip(ip)
       ,_port(port)
  {
    signal(SIGCHLD,SIG_IGN);
  }
   
  void ProcConnect(TcpSocket& newsock,string& ip,uint16_t port,Handler handler)
  {
    pid_t id = fork();
    if(id < 0){
      perror("use fork");
      exit(1);
    }
    else if(id == 0)
    {
      while(1){
      //child
      string req;
      newsock.Recv(&req);
      string res;
      handler(req,&res);
      newsock.Send(res);
      cout<<ip<<"-"<<port<<" req:"<<req<<" | res:"<<res<<endl;
      }
    }
    else{
      //father
      //父进程直接结束即可，不需要wait子进程，因为已经将SIGCHILD信号捕捉为忽略
      //父进程也不能wait，如果wait不能再次快速调用accept
      //父进程需要关闭newsock
      newsock.Close();
      return ;
    } 
  }

  void Start(Handler handler)
  {
    //创建socket
    listen_sock.Socket();
    //绑定ip与端口号
    listen_sock.Bind(_ip,_port);
    //监听
    listen_sock.Listen(5);
    while(1)
    {
      TcpSocket newsock;
      string ip;
      uint16_t port;
      listen_sock.Accept(&newsock,&ip,&port);
      cout<<"client:"<<ip.c_str()<<"-"<<port<<"connect"<<endl;
      ProcConnect(newsock,ip,port,handler);
      }
  }

  private:
    TcpSocket listen_sock;
    string _ip;
    uint16_t _port;
};
