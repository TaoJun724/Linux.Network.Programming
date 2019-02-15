#include"Tcp_Server.hpp"
#include<unordered_map>

unordered_map<string,string> dict;
void Translate(string& req,string* res)
{
  auto it = dict.find(req);
  if(it == dict.end())
  {
    *res = "字典中无此单词";
    return ;
  }
  *res = it->second;
}

int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    cout<<"Usage:./Tcp_Server [ip][port]"<<endl;
    return 1;
  }

  //初始化词典
  dict.insert(make_pair("hello","你好"));
  dict.insert(make_pair("baby","宝贝"));

  string ip(argv[1]);
  TcpServer server(ip,atoi(argv[2]));
  server.Start(Translate);

  return 0;
}
