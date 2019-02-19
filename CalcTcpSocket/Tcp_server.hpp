#pragma once 

#include<string.h>
#include"Tcp_Socket.hpp"
#include"ThreadPool.hpp"
#include<unordered_map>

unordered_map<string,string> dict;

void Translate(string& req,string* res)
{
  auto it = dict.find(req);
  if(it == dict.end())
  {
    *res = "查询无果";
    return ;
  }
  *res = it->second;
}


//typedef void (*Handler)(string& req, string* res);
//typedef struct ThreadArg
//{
//   TcpSocket new_sock;
//   string ip;
//   uint16_t port;
//   Handler handler;
//}ThreadArg;
//
class TcpServer
{
  public:
      TcpServer(string ip, uint16_t port)
        :_pool(5)
        ,_ip(ip)
        ,_port(port)
  {}

//      static void SingleDeal(ThreadArg* arg)
//      {
//        while(1)
//        {
//          string req;
//          arg->new_sock.Recv(&req);
//          
//          string res;
//          arg->handler(req, &res);
//
//          arg->new_sock.Send(res);
//          cout << "client:" << arg->ip << "--" << arg->port << "req:" << req << " .res:" << res << endl;
//        }
//      }
//
//      static void* Routine(void* arg)
//      {
//          pthread_detach(pthread_self());
//          ThreadArg* ptr = reinterpret_cast<ThreadArg*>(arg);
//        SingleDeal(ptr);
//       ptr->new_sock.Close();
//       delete ptr;
//        ptr = NULL;
//      }
//
      
      static void server(TcpSocket sock)
       {
//          //初始化字典
//          dict.insert(make_pair("baby","宝贝"));
//
//          while(1)
//          {
//            string req;
//            sock.Recv(&req);
//            string res;
//            Translate(req,&res);
//
//            cout<<req<<"-"<<res<<endl;
//            sock.Send(res);
//          }
//          sock.Close();
           

         Request_t requ;
         Respon_t resp;

         for(;;)
         {
           memset(&requ,0,sizeof(requ));
           memset(&resp,0,sizeof(resp));
           sock.Recv(requ);
           resp.flag = 0;
           switch(requ.op){
             case 1:
               resp.res = requ.x + requ.y;
               break;
             case 2:
               resp.res = requ.x - requ.y;
               break; 
             case 3:
               resp.res = requ.x * requ.y;
               break; 
             case 4:
               {
                 if(requ.y == 0){
                   resp.flag = 1;
                 }else{
                   resp.res = requ.x / requ.y;
                 }
               }
               break;
             case 5:
               resp.res = requ.x % requ.y;
               break;
              default:
               resp.flag = 2;
               cout<<"[左操作数][运算符(12345--->+-*/%)][右操作数]" << endl;
               break;
           }
           sock.Send(resp);
         }
         sock.Close();
     }
       
      void Start()
      {
        listen_sock.Socket();
        listen_sock.Bind(_ip,_port);
        listen_sock.Listen(5);
        _pool.InitPool();
        while(1)
        {
          TcpSocket new_sock;
          string ip;
          uint16_t port;
          listen_sock.Accept(&new_sock, &ip, &port);

           cout << "client:" << ip.c_str() << "--" << port << " connect" << endl;
        
           Task t(new_sock,server);
           _pool.AddTask(t);
        }
      }
  private:
      TcpSocket listen_sock;
      string _ip;
      ThreadPool _pool;
      uint16_t _port;
};
