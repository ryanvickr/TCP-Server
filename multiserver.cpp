#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <sstream>
 
using namespace std;
 
int main()
{
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
 
    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(3001);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    // Create the master file descriptor set and zero it
	fd_set master;
    FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 

	FD_SET(listening, &master);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true; 

	while (running)
	{
        cout << "Running..." << master.fds_bits[0] << endl;
        fd_set copy = master;
        cout << "Copied master" << copy.fds_bits[0]<< endl;

		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
        cout << "There are " << socketCount << " sockets." << endl;

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++) {
            int socket = copy.fds_bits[i];
            cout << "Socket: " << socket << endl;

            if (socket == listening)
            {
                // accept new connection
                cout << "Listening to port..." << endl;
                int clientSocket = accept(listening, nullptr, nullptr);

                // add new connection to list of connected clients
                FD_SET(clientSocket, &master);

                // send welcome message to connected client
                string welcomeMsg = "What's good";
                send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

                // TODO: broadcast we have a new connection
            }
            else {
                cout << "Accepting message..." << endl;
                //accept message
                char buff[4096];
                memset(buff, 0, 4096);

                int bytesIn = recv(socket, buff, 4096, 0);
                if (bytesIn <= 0) {
                    //drop client
                    close(socket);
                    FD_CLR(socket, &master);
                }
                else {
                    //send the message to the other clients (not listening)
                    for(int j = 0; j < socketCount; j++) {
                        int outSocket = master.fds_bits[i];

                        if (outSocket != listening && outSocket != socket)
                        {
                            send(outSocket, buff, bytesIn, 0);
                        }
                        
                    }
                }
                
            }
        }
	}
 
    // // Wait for a connection
    // sockaddr_in client;
    // socklen_t clientSize = sizeof(client);
 
    // int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    // char host[NI_MAXHOST];      // Client's remote name
    // char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    // memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    // memset(service, 0, NI_MAXSERV);
 
    // if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    // {
    //     cout << host << " connected on port " << service << endl;
    // }
    // else
    // {
    //     inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    //     cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    // }
 
    // // Close listening socket
    // close(listening);
 
    // // While loop: accept and echo message back to client
    // char buf[4096];
 
    // while (true)
    // {
    //     memset(buf, 0, 4096);
 
    //     // Wait for client to send data
    //     int bytesReceived = recv(clientSocket, buf, 4096, 0);
    //     if (bytesReceived == -1)
    //     {
    //         cerr << "Error in recv(). Quitting" << endl;
    //         break;
    //     }
 
    //     if (bytesReceived == 0)
    //     {
    //         cout << "Client disconnected " << endl;
    //         break;
    //     }
 
    //     cout << string(buf, 0, bytesReceived) << endl;
 
    //     // Echo message back to client
    //     send(clientSocket, buf, bytesReceived + 1, 0);
    // }
 
    // // Close the socket
    // close(clientSocket);
 
    // return 0;
}