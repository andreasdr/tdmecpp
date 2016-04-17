#ifndef ECHOTCPSERVERCLIENT_H
#define ECHOTCPSERVERCLIENT_H

#include <sstream>

#include <libtdme/network/shared/NIOTCPSocket.h>
#include <libtdme/network/udpserver/NIOUDPServer.h>
#include <libtdme/network/udpserver/NIOUDPServerClient.h>

#include "EchoUDPServer.h"

using namespace std;
using namespace TDMENetwork;

class EchoUDPServerClient : public NIOUDPServerClient {
	friend class EchoUDPServer;

	public:
		EchoUDPServerClient(const uint32_t clientId, const std::string& ip, const unsigned int port);

	protected:
		virtual ~EchoUDPServerClient();

		virtual void onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (exception);

		void onInit() throw (exception);
		void onClose() throw (exception);
		void onCustom(const string& type) throw (exception);
};

#endif
