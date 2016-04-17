#include <iostream>
#include <sstream>

#include "EchoTCPServer.h"

using namespace std;
using namespace TDMENetwork;

CRHShutdown::CRHShutdown() : NIOServerClientRequestHandler<NIOTCPServerClient,string>("/shutdown") {}

CRHShutdown::~CRHShutdown() {
}

void CRHShutdown::handleRequest(NIOTCPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception) {
	cout << "received /shutdown, shutting down client" << endl;
	client->shutdown();
}

CRHDefault::CRHDefault() : NIOServerClientRequestHandler<NIOTCPServerClient,string>("/default") {}

CRHDefault::~CRHDefault() {
}

void CRHDefault::handleRequest(NIOTCPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception) {
	stringstream* outFrame = client->createFrame();
	*outFrame << data;
	client->send(outFrame);
}

EchoTCPServer::EchoTCPServer(string host, unsigned int port, unsigned int maxCCU) : NIOTCPServer("echo", host, port, maxCCU) {
	std::cout << "Starting echo tcp server @ " << host << ":" << port << endl;
	setIOThreadCount(2);
	setWorkerThreadCount(8);
	requestHandlerHub.addHandler(new CRHShutdown());
	requestHandlerHub.setDefaultHandler(new CRHDefault());
}

EchoTCPServer::~EchoTCPServer() {
}

NIOTCPServerClient* EchoTCPServer::accept(NIOTCPSocket& socket) {
	std::cout << "accepting client connection with '" << socket.getAddress() << "'" << endl;
	// create client
	EchoTCPServerClient* client = new EchoTCPServerClient(socket);
	// set up framing
	client->initFraming(new NIOTCPTelnetFraming(client));
	//
	return client;
}
