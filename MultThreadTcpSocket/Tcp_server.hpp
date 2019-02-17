#pragma once 

#include"Tcp_Socket.hpp"
#include<pthread.h>
#include<sys/types.h>

typedef void (*Handler)(string& req, string* res);
typedef struct ThreadArg
{
   TcpSocket new_sock;
   string ip;
   uint16_t port;
   Handler handler;
}ThreadArg;

class TcpServer
{
  public:
      TcpServer(string& ip, uint16_t port)
            :_ip(ip)
            ,_port(port)
  {}

      static void SingleDeal(ThreadArg* arg)
      {
        while(1)
        {
          string req;
          arg->new_sock.Recv(&req);
          
          string res;
          arg->handler(req, &res);

          arg->new_sock.Send(res);
          cout << "client:" << arg->ip << "--" << arg->port << "req:" << req << " .res:" << res << endl;
        }
      }

      static void* Routine(void* arg)
      {
          pthread_detach(pthread_self());
          ThreadArg* ptr = reinterpret_cast<ThreadArg*>(arg);
        SingleDeal(ptr);
       ptr->new_sock.Close();
       delete ptr;
        ptr = NULL;
      }
      
      void Start(Handler handler)
      {
        listen_sock.Socket();
        listen_sock.Bind(_ip,_port);
        listen_sock.Listen(5);
        while(1)
        {
          ThreadArg* arg = new ThreadArg();
          arg->handler = handler;
          listen_sock.Accept(&arg->new_sock, &arg->ip, &arg->port);

           cout << "client:" << arg->ip.c_str() << "--" << arg->port << " connect" << endl;
        
           pthread_t tid;
           pthread_create(&tid, NULL, Routine, (void*)arg);
        }
      }
  private:
      TcpSocket listen_sock;
      string _ip;
      uint16_t _port;
};
