/**
* @version $Id: 2377db0d88df02b4ab3760a4a1c365e41d9e3dcd $
*/

#include <signal.h>

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Queue.h>

#include "EchoUDPServer.h"
#include "EchoUDPServerClient.h"

using namespace std;
using namespace TDMEThreading;
using namespace TDMENetwork;

namespace TDMENetwork {

	class ServerBroadcaster : public TDMEThreading::Thread {
		public: 
			ServerBroadcaster(EchoUDPServer *server) : TDMEThreading::Thread("broadcaster"), server(server) {}

			virtual ~ServerBroadcaster() {
			}

			virtual void run() {
				while (isStopRequested() == false) {
					TDMEThreading::Thread::sleep(1000);
					if (++time == 5) {
						// get client key list
						EchoUDPServer::ClientKeySet clientKeySet = server->getClientKeySet();
						for (EchoUDPServer::ClientKeySet::iterator i = clientKeySet.begin(); i != clientKeySet.end(); ++i) {
							EchoUDPServerClient* client = static_cast<EchoUDPServerClient*>(server->getClientByKey(*i));
							if (client != NULL) {
								stringstream* frame = client->createFrame();
								*frame << "broadcast test";
								client->send(frame, true);
								client->releaseReference();
							}
						}
						time = 0;
					}
				}
			}
		private:
			EchoUDPServer *server;
			unsigned int time;
	};

};

EchoUDPServer* server = NULL;
ServerBroadcaster* bc = NULL;

void sigHandlerINT(int signal) {
	cout << "Interrupt signal catched" << endl;
	if (server != NULL) {
		// stop broad caster
		server->stop();
	}
}

int main(int argc, char *argv[]) {
	// install SIGNINT handler
	if (signal(SIGINT, sigHandlerINT) == SIG_ERR) {
		cout << "Can't install signal handler for SIGINT" << endl;
	}

	// start echo server
	server = new EchoUDPServer("127.0.0.1", 10000, 1000);
	bc = new ServerBroadcaster(server);
	bc->start();
	server->start();

	// wait until server has been stopped
	server->join();

	// stop and wait for broad caster
	bc->stop();
	bc->join();

	// delete server and broadcaster
	delete server;
	delete bc;

	return 0;
}
