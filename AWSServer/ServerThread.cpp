#include "ServerThread.h"
#include "SocketThread.h"
#include "clientlist.h"
#include <list>

using namespace Sync;

std::list<Socket&> clients;
std::list<Socket&>::iterator clientIterator;

ServerThread::ServerThread(SocketServer& server)
: server(server)
{}

ServerThread::~ServerThread()
{
    
    // Close the client sockets
    for (auto thread : socketThreads)
    {
        try
        {
            std::cout<<"Closing"<<std::endl;
            // Close the socket
            Socket& toClose = thread->GetSocket();
            toClose.Close();
        }
        catch (...)
        {
            // If already closed, this will cause an exception
        }
    }

    // Terminate the thread loops
    terminate = true;
}

long ServerThread::ThreadMain()
{   
    while(true)
    {
        try
        {
            // Wait for a client socket connection
            Socket* newConnection = new Socket(server.Accept());
            std::cout<<"Connected!"<< std::endl;

            // Pass a reference to this pointer into a new socket thread
            Socket& socketReference = *newConnection;
            socketThreads.push_back(new SocketThread(socketReference, terminate));
            clients.push_back(socketReference); //add client to list
        }
        catch (TerminationException terminationException)
        {
            return terminationException;
        }
        catch (std::string error)
        {
            std::cout << std::endl << "[Error] " << error << std::endl;
            return 1;
        }
    }
}
