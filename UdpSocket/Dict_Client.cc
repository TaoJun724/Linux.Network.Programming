#include"Udp_client.hpp"
#include<iostream>
using namespace std;


int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    printf("Usage./Dict_Client[ip] [port]\n");
    return 1;
  }

  UdpClient client(argv[1],atoi(argv[2]));
  for(;;){
    string word;
    cout<<"请输入你要查询的单词:";
    cin>>word;
    if(word=="quit")
    {
      cout<<"bye"<<endl;
      break;
    }
    client.SendTo(word);
    string result;
    client.RecvFrom(&result);
    cout<<word<<"意思"<<result<<endl;
  }
  return 0 ;
}

