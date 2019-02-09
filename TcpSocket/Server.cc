#include"TcpServer.hpp"
#include<unordered_map>


unordered_map<string,string> dict;

void Translate(string& req, string* res)
{
    auto it = dict.find(req);
      if(it == dict.end())
      {
            *res = "词典中没有该单词";
                return;
                  
      }
        *res = it->second;

}
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
          cout << "Usage: ./tcp_server [ip][port]" << endl;
              return 1;
                
    }
   dict.insert(make_pair("haha","哈哈"));
      dict.insert(make_pair("happy", "快乐"));
    

          TcpServer server(argv[1],atoi(argv[2])); 
            server.Start(Translate);

              return 0;
}
