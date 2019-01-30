.PHONY:all
all:Dict_Client Dict_Server

cc=g++

Dict_Client:Dict_Client.cc Udp_client.hpp Udp_Socket.hpp 
	$(cc) -o $@ -std=c++11 $^ 

Dict_Server:Dict_Server.cc Udp_Server.hpp Udp_Socket.hpp 
	$(cc) -o $@ -std=c++11 $^

.PHONY:clean
clean:
	rm -f Dict_Client Dict_Server
