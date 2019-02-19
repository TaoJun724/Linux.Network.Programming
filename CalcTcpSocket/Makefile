.PHONY:all
all:Client Server

Client:client.cc Tcp_Client.hpp Tcp_Socket.hpp 
	g++ -o $@ -std=c++11 $^
Server:Server.cc Tcp_Socket.hpp Tcp_server.hpp 
	g++ -o $@ $^ -std=c++11 -lpthread  -fpermissive

.PHONY:clean
clean:
	rm -f Client Server
