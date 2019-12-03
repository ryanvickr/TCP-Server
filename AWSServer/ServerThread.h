#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <list>
#include <vector>
#include <string>
#include <list>

using namespace Sync;

extern std::list<Socket&> clients;
extern std::list<Socket&>::iterator clientIterator;

class SocketThread;


class ServerThread: public Thread{
private:
    SocketServer& server;
    bool terminate = false;
public:
std::vector<SocketThread*> socketThreads;
    ServerThread(SocketServer& server);
    ~ServerThread();
    virtual long ThreadMain();
};

#endif