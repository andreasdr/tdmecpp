#ifndef ECHOTCPSERVER_H
#define ECHOTCPSERVER_H

#include <string>

#include <libtdme/network/tcpserver/NIOTCPServer.h>
#include <libtdme/network/tcpserver/NIOTCPServerClient.h>
#include <libtdme/network/tcpserver/NIOTCPTelnetFraming.h>

#include <libtdme/network/shared/NIOServerClientRequestHandler.h>
#include <libtdme/network/shared/NIOServerClientRequestHandlerHub.h>

#include "EchoTCPServerClient.h"

using namespace std;
using namespace TDMENetwork;

class CRHShutdown : public NIOServerClientRequestHandler<NIOTCPServerClient,string> {
	public:
		CRHShutdown();

		virtual ~CRHShutdown();

		void handleRequest(NIOTCPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception);
};

class CRHDefault : public NIOServerClientRequestHandler<NIOTCPServerClient,string> {
	public:
		CRHDefault();

		virtual ~CRHDefault();

		void handleRequest(NIOTCPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (exception);
};

class EchoTCPServer : public NIOTCPServer {
	friend class EchoTCPServerClient;
	public:
		EchoTCPServer(string host, unsigned int port, unsigned int maxCCU);

		virtual ~EchoTCPServer();
	protected:
		NIOTCPServerClient* accept(NIOTCPSocket& socket);

		NIOServerClientRequestHandlerHub<NIOTCPServerClient,string> requestHandlerHub;
};

#endif
