#include "EchoTCPServerClient.h"

#include <iostream>
#include <typeinfo>

#include <libtdme/globals/Logger.h>
#include <libtdme/globals/RTTI.h>

EchoTCPServerClient::EchoTCPServerClient(NIOTCPSocket &socket) : NIOTCPServerClient(socket) {
}

EchoTCPServerClient::~EchoTCPServerClient() {
	std::cout << "EchoTCPServerClient::~EchoTCPServerClient()" << endl;
}

void EchoTCPServerClient::onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (exception) {
	// fetch command
	string command = frame->str();

	// do the handler logic
	static_cast<EchoTCPServer*>(server)->requestHandlerHub.handleRequest(
		this,
		command,
		command,
		messageId,
		retries
	);
}

void EchoTCPServerClient::onInit() throw (exception) {
	std::cout << "initiated connection with '" << getIp() << ":" << getPort() << "'"<< endl;
}

void EchoTCPServerClient::onClose() throw (exception) {
	std::cout << "closed connection with '" << getIp() << ":" << getPort() << "'"<< endl;
}

void EchoTCPServerClient::onCustom(const string& type) throw (exception) {
	std::cout << "custom event '" << type << "' with '" << getIp() << ":" << getPort() << "'"<< endl;
}
