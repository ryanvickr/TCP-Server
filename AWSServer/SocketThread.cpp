#include "SocketThread.h"
#include "ServerThread.h"
using namespace Sync;
std::vector<std::string> msgs;
SocketThread::SocketThread(Socket& socket, bool& terminate, std::list<Socket>& clients)
: socket(socket), terminate(terminate), clients(clients)
{}

SocketThread::~SocketThread()
{}

Socket& SocketThread::GetSocket()
{
    return socket;
}

long SocketThread::ThreadMain()
{  
    bool firstRun = true;

    // If terminate is ever flagged, we need to gracefully exit
    while(!terminate)
    {
        try
        {
            //get the username
            if (firstRun)
            {
                socket.Write(ByteArray("Enter username!"));

                socket.Read(data);
                std::string data_str = data.ToString();
                this->username = data_str;
                std::cout<<data_str<<std::endl;
                socket.Write(ByteArray("Username is: " + this->username));
                firstRun = false;
            }
            //normal execution (after getting username)
            else {
                //wipe bytearray
                data.v.clear();

                socket.Read(data);
                std::string data_str = data.ToString();
                bool disconnect = false;
                if (data_str == "-disconnect")
                {
                    //remove from clients list and close this thread
                    for (int j = 0; j < clients.size(); j++)
                    {
                        Socket currentSock = clients.back();
                        clients.pop_back();
                        if (currentSock.GetFD() == socket.GetFD())
                        {
                            std::cout << this->username << " has disconnected." << std::endl;
                            socket.Close();
                            disconnect = true;
                            break;
                        }
                        else {
                            clients.push_front(currentSock);
                        }
                    }
                }
                else if (data_str.empty())
                {
                    continue;
                }
                
                if (disconnect) break;
                

                std::cout << data_str << std::endl;
                
                // loop through clients and write to their sockets.
                for (int j = 0; j < clients.size(); j++)
                {
                    
                    Socket currentSocket = clients.back();
                    currentSocket.Write(ByteArray(data_str));
                    clients.pop_back();
                    clients.push_front(currentSocket);
                }
            }
        }
        catch (...)
        {
            // We catch the exception, but there is nothing for us to do with it here. Close the thread.
            std::cerr << "Problem with " << this->username << "." << std::endl;
        }

        i++;
    }

    return 0;
}
