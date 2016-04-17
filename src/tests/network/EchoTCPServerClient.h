#ifndef ECHOTCPSERVERCLIENT_H
#define ECHOTCPSERVERCLIENT_H

#include <sstream>

#include <libtdme/network/shared/NIOTCPSocket.h>
#include <libtdme/network/tcpserver/NIOTCPServer.h>
#include <libtdme/network/tcpserver/NIOTCPServerClient.h>

#include "EchoTCPServer.h"

using namespace std;
using namespace TDMENetwork;

class EchoTCPServerClient : public NIOTCPServerClient {
	friend class EchoTCPServer;

	public:
		EchoTCPServerClient(NIOTCPSocket &socket);

	protected:
		virtual ~EchoTCPServerClient();

		virtual void onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (exception);

		void onInit() throw (exception);
		void onClose() throw (exception);
		void onCustom(const string& type) throw (exception);
};

#endif
