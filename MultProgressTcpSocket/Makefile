.PHONY:all
all:Dict_Client Dict_Server

Dict_Client:Dict_Client.cc Tcp_Client.hpp Tcp_Socket.hpp 
	g++ -o $@ -std=c++11 $^
Dict_Server:Dict_Server.cc Tcp_Socket.hpp Tcp_Server.hpp 
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f Dict_Client Dict_Server
