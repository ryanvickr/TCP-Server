#include "SocketThread.h"
#include "ServerThread.h"
#include "clientlist.h"
using namespace Sync;
std::vector<std::string> msgs;
SocketThread::SocketThread(Socket& socket, bool& terminate)
: socket(socket), terminate(terminate)
{}

SocketThread::~SocketThread()
{}

Socket& SocketThread::GetSocket()
{
    return socket;
}

long SocketThread::ThreadMain()
{  
                

    // If terminate is ever flagged, we need to gracefully exit
    while(!terminate)
    {

        try
        {
                if(i==0){
                    std::string msg = "Enter your username:";
                    socket.Write(ByteArray(msg));

                }
                // Wait for data
                //socket.Read(data);
            
                // Perform operations on the data
                //std::string data_str = data.ToString();
                
                if(this->username==""){
                    socket.Read(data);
                    std::string data_str = data.ToString();
                    this->username=data_str;
                    std::cout<<data_str<<std::endl;
                    
                    // loop through clients and write to their sockets.
                    for (clientIterator = clients.begin(); clientIterator != clients.end; clientIterator++)
                    {
                        Socket& currentSocket = (*clientIterator);
                        currentSocket.Write(ByteArray(data_str));
                    }
                    
                    // socket.Write(ByteArray(data_str)); //send message back to user
                }else {
                    
                    for(int j=0;j<msgs.size();j++){
                        socket.Write(ByteArray(msgs.at(j)));
                    }
                    socket.Read(data);
                    std::string data_str = data.ToString();
                    msgs.push_back(data_str);
                    

                }
               

                // Send it back
                i++;
        }
        catch (...)
        {
            // We catch the exception, but there is nothing for us to do with it here. Close the thread.
        }
    }

    return 0;
}
