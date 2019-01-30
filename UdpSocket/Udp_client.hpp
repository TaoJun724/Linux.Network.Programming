#ifndef __UDP_CLIENT_HPP__
#define __UDP_CLIENT_HPP__ 
#include"Udp_Socket.hpp"


class UdpClient
{
  public:
    UdpClient(const string& ip,uint16_t port):ip_(ip),port_(port)
  {
    assert(sock_.Socket());
  }

    ~UdpClient()
    {
      sock_.Close();
    }

    bool RecvFrom(string* buf)
    {
      return sock_.RecvFrom(buf);
    }

    bool SendTo(const string& buf)
    {
      return sock_.SendTo(buf,ip_,port_);
    }
  private:
    UdpSocket sock_;
    string ip_;
    uint16_t port_;
};

#endif
