
#include "thread.h"
#include "socket.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace Sync;

bool notDone = true;

// This thread handles the connection to the server
class ClientThread : public Thread
{
private:
	// Reference to our connected socket
	Socket& socket;

	// Data to send to server
	ByteArray data;
	ByteArray temp;
	std::string data_str;
public:
	ClientThread(Socket& socket)
	: socket(socket)
	{}

	~ClientThread()
	{
		std::cout<<"Thread was deleted"<<std::endl;
	}

	virtual long ThreadMain()
	{
		try{
			int result = socket.Open();
		}catch(...){
			std::cout<<"Server is not running"<<std::endl;
			notDone = false;
			return 0;
		}
		
		while(1){
			std::cout << "Please input your data (done to exit): ";
			std::cout.flush();

			// Get the data
			std::getline(std::cin, data_str);
			if(data_str == "done")
				break;
			data = ByteArray(data_str);
			temp = data;
			// Write to the server
			
				socket.Write(data);

				// Get the response
				socket.Read(data);
				data_str = data.ToString();
				if(data_str == ""){
					std::cout<<"No Server running" << std::endl;
					break;
				}
					
				std::cout << "Server Response: " << data_str << std::endl;
			
		
			
		}
		notDone = false;
		std::cout <<"done"<<std::endl;
		
		return 0;
	}
};

int main(void)
{
	// Welcome the user 
	std::cout << "SE3313 Lab 3 Client" << std::endl;

	// Create our socket
	Socket socket("127.0.0.1", 3001);
	ClientThread clientThread(socket);
	
	while(notDone)
	{
		sleep(1);
	}
	
	socket.Close();

	return 0;
}
