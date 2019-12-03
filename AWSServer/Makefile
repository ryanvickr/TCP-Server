all: Server

Server : Server.o thread.o socket.o socketserver.o Blockable.o ServerThread.o SocketThread.o
	g++ -o Server Server.o thread.o socket.o socketserver.o Blockable.o ServerThread.o SocketThread.o -pthread -l rt

Blockable.o : Blockable.h Blockable.cpp
	g++ -c Blockable.cpp -std=c++11

Server.o : Server.cpp socketserver.h ServerThread.h 
	g++ -c Server.cpp -std=c++11

thread.o : thread.cpp thread.h
	g++ -c thread.cpp -std=c++11

socket.o : socket.cpp socket.h
	g++ -c socket.cpp -std=c++11

socketserver.o : socketserver.cpp socket.h socketserver.h
	g++ -c socketserver.cpp -std=c++11

ServerThread.o : ServerThread.cpp thread.h socketserver.h ServerThread.h SocketThread.h 
	g++ -c ServerThread.cpp -std=c++11
	
SocketThread.o : SocketThread.cpp thread.h SocketThread.h ServerThread.h 
	g++ -c SocketThread.cpp -std=c++11