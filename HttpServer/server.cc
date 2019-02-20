#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

class Server 
{
  public:
    Server(string ip,uint16_t port)
      :_sock(-1)
      ,_ip(ip)
      ,_port(port)
  {}

    void Start()
    {
       _sock = socket(AF_INET,SOCK_STREAM,0);
       if(_sock < 0)
       {
         perror("use socket");
         return ;
       }
       struct sockaddr_in addr;
       addr.sin_family = AF_INET;
       addr.sin_addr.s_addr = inet_addr(_ip.c_str());
       addr.sin_port = htons(_port);
       //绑定
       int ret = bind(_sock,(sockaddr*)&addr,sizeof(addr));
       if(ret < 0){
         perror("use bind");
         return ;
       }
       //监听
       ret = listen(_sock,5);
       if(ret < 0){
         perror("use listen");
         return ;
       }
       while(1)
       {
         struct sockaddr_in client_addr;
         socklen_t len = sizeof(client_addr);
        int newsock = accept(_sock, (struct sockaddr*)&client_addr, &len);
        if(newsock < 0)
        {
          perror("use accept");
          return ;
        }
        cout<<"a client connect!"<<endl;
        char req[1024];//用来接收请求报文
        int  rs = recv(newsock,req,sizeof(req)-1,0);
        if(rs < 0){
          perror("use recv");
          return ;
        }
        req[rs] = 0;         
        cout << "Req:" << req << endl;

        const char* hello = "<h1>hello world</h1>";
        char res[1024];
        //状态行 正文长度 空行 响应正文
       sprintf(res, "HTTP/1.0 200 OK\nContent-Length:%lu\n\n%s",strlen(hello),hello);
        send(newsock, res, strlen(res), 0);
        close(newsock);
       }
    }
  private:
    int _sock;
    string _ip;
    u_int16_t _port;
};


int main(int argc,char* argv[])
{
  if(argc != 3){
    cout<<"Usage:./server[ip][port]"<<endl;
  }
  
  Server* s = new Server(argv[1],atoi(argv[2]));

  s->Start();

  delete s;
  return 0;
}
