#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include "socket.h"
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

class SocketServer : public Sync::Blockable
{
private:
    int pipeFD[2];
    Sync::Event terminator;
    sockaddr_in socketDescriptor;
public:
    SocketServer(int port);
    ~SocketServer();
    Sync::Socket Accept(void);
    void Shutdown(void);
};

#endif // SOCKETSERVER_H
