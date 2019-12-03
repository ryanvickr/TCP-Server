#include <list>
#include "ServerThread.h"
#include "SocketThread.h"

using namespace Sync;

extern std::list<Socket&> clients;
extern std::list<Socket&>::iterator clientIterator;