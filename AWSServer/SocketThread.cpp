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
                std::cout<<data_str<< " SocketFD: " << socket.GetFD() << std::endl;
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
                    clients.remove(socket);
                    return 0;
                }
                else if (data_str.empty())
                {
                    continue;
                }
                

                std::cout << data_str << " Socket: " << socket.GetFD() << std::endl;

                if (data_str.length < 10)
                {
                    data_str = data_str + "             ";
                }
                
                
                // loop through clients and write to their sockets.
                for (int j = 0; j < clients.size(); j++)
                {
                    Socket currentSocket = clients.back();
                    currentSocket.Write(this->username + ": " + data_str);
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
