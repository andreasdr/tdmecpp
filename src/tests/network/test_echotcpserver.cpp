/**
* @version $Id: c4e9e43d6ec3fbce76d2790e43bcfc7fee3cecdc $
*/

#include <signal.h>

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Queue.h>

#include "EchoTCPServer.h"
#include "EchoTCPServerClient.h"

using namespace std;
using namespace TDMEThreading;
using namespace TDMENetwork;

namespace TDMENetwork {

	class ServerBroadcaster : public TDMEThreading::Thread {
		public: 
			ServerBroadcaster(EchoTCPServer *server) : TDMEThreading::Thread("broadcaster"), server(server) {}

			virtual ~ServerBroadcaster() {
			}

			virtual void run() {
				while (isStopRequested() == false) {
					TDMEThreading::Thread::sleep(1000);
					if (++time == 5) {
						// get client key list
						EchoTCPServer::ClientKeySet clientKeySet = server->getClientKeySet();
						for (EchoTCPServer::ClientKeySet::iterator i = clientKeySet.begin(); i != clientKeySet.end(); ++i) {
							EchoTCPServerClient* client = static_cast<EchoTCPServerClient*>(server->getClientByKey(*i));
							if (client != NULL) {
								stringstream* frame = client->createFrame();
								*frame << "broadcast test";
								client->send(frame);
								client->releaseReference();
							}
						}
						time = 0;
					}
				}
			}
		private:
			EchoTCPServer *server;
			unsigned int time;
	};

};

EchoTCPServer* server = NULL;
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
	server = new EchoTCPServer("127.0.0.1", 10000, 1000);
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
