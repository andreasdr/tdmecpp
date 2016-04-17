#include <iostream>
#include <sstream>

#include "EchoUDPServer.h"

using namespace std;
using namespace TDMENetwork;

CRHShutdown::CRHShutdown() : NIOServerClientRequestHandler<NIOUDPServerClient,string>("/shutdown") {}

CRHShutdown::~CRHShutdown() {
}

void CRHShutdown::handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise request shutdown
	cout << "received /shutdown, shutting down client" << endl;
	client->shutdown();
}

CRHDefault::CRHDefault() : NIOServerClientRequestHandler<NIOUDPServerClient,string>("/default") {}

CRHDefault::~CRHDefault() {
}

void CRHDefault::handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise echo the input
	stringstream* outFrame = client->createFrame();
	*outFrame << data;
	client->send(outFrame, true);
}

EchoUDPServer::EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU) : NIOUDPServer("echo", host, port, maxCCU) {
	std::cout << "Starting echo udp server @ " << host << ":" << port << endl;
	setIOThreadCount(2);
	setWorkerThreadCount(8);
	requestHandlerHub.addHandler(new CRHShutdown());
	requestHandlerHub.setDefaultHandler(new CRHDefault());
}

EchoUDPServer::~EchoUDPServer() {
}

NIOUDPServerClient* EchoUDPServer::accept(const uint32_t clientId, const std::string& ip, const unsigned int port) {
	std::cout << "accepting client connection with '" << ip << ":" << port << "'" << std::endl;

	// create client
	EchoUDPServerClient* client = new EchoUDPServerClient(clientId, ip, port);

	//
	return client;
}
