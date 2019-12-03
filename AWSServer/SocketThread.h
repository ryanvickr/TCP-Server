#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <list>
#include <vector>
#include <string>

class SocketThread : public Thread{
private:
    Sync::Socket& socket;
    int i=0;
    Sync::ByteArray data;
    std::string username;
    bool& terminate;

public:
    SocketThread(Sync::Socket& socket, bool& terminate);
    ~SocketThread();
    Sync::Socket& GetSocket();
    virtual long ThreadMain();
};

#endif