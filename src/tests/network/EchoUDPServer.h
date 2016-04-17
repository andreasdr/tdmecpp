#ifndef ECHOTCPSERVER_H
#define ECHOTCPSERVER_H

#include <string>

#include <libtdme/network/udpserver/NIOUDPServer.h>
#include <libtdme/network/udpserver/NIOUDPServerClient.h>

#include <libtdme/network/shared/NIOServerClientRequestHandler.h>
#include <libtdme/network/shared/NIOServerClientRequestHandlerHub.h>

#include "EchoUDPServerClient.h"

using namespace std;
using namespace TDMENetwork;

class CRHShutdown : public NIOServerClientRequestHandler<NIOUDPServerClient,string> {
	public:
		CRHShutdown();

		virtual ~CRHShutdown();

		void handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception);
};

class CRHDefault : public NIOServerClientRequestHandler<NIOUDPServerClient,string> {
	public:
		CRHDefault();

		virtual ~CRHDefault();

		void handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception);
};

class EchoUDPServer : public NIOUDPServer {
	friend class EchoUDPServerClient;
	public:
		EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU);

		virtual ~EchoUDPServer();
	protected:
		NIOUDPServerClient* accept(const uint32_t clientId, const std::string& ip, const unsigned int port);

		NIOServerClientRequestHandlerHub<NIOUDPServerClient,string> requestHandlerHub;
};

#endif
