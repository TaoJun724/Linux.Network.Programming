.PHONY:all
all:client server

cc=g++

client:Client.cc TcpClient.hpp TcpSocket.hpp 
	$(cc) -o $@ -std=c++11 $^

server:Server.cc TcpServer.hpp TcpSocket.hpp 
	$(cc) -o $@ -std=c++11 $^

.PHONY:clean
clean:
	rm -f client server
