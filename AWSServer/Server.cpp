#include "ServerThread.h"
#include "socketserver.h"


using namespace Sync;

int main(void)
{
    // Welcome the user
    std::cout << "SE3313 Project Server" << std::endl;
    std::cout << "Press enter to terminate the server...";
    std::cout.flush();

    // Create our server
    SocketServer server(3000);    

    // Need a thread to perform server operations
    ServerThread serverThread(server);

    // This will wait for input to shutdown the server
    FlexWait cinWaiter(1, stdin);
    cinWaiter.Wait();
    std::cin.get();

    // Shut down and clean up the server
    server.Shutdown();
    return 0;
}