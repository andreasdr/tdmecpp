#include "EchoUDPServerClient.h"

#include <iostream>
#include <typeinfo>

#include <libtdme/globals/Logger.h>
#include <libtdme/globals/RTTI.h>

EchoUDPServerClient::EchoUDPServerClient(const uint32_t clientId, const std::string& ip, const unsigned int port) :
	NIOUDPServerClient(clientId, ip, port) {
}

EchoUDPServerClient::~EchoUDPServerClient() {
	std::cout << "EchoUDPServerClient::~EchoUDPServerClient()" << endl;
}

void EchoUDPServerClient::onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (exception) {
	string command;
	char c;
	while(true) {
		// extract character from frame
		frame->get(c);

		// exit if eof
		if (frame->eof() == true) {
			break;
		}

		// no eof, add character to command
		command+= c;
	}

	// do the handler logic
	static_cast<EchoUDPServer*>(server)->requestHandlerHub.handleRequest(
		this,
		command,
		command,
		messageId,
		retries
	);
}

void EchoUDPServerClient::onInit() throw (exception) {
	std::cout << "initiated connection with '" << getIp() << ":" << getPort() << "'"<< endl;
}

void EchoUDPServerClient::onClose() throw (exception) {
	std::cout << "closed connection with '" << getIp() << ":" << getPort() << "'"<< endl;
}

void EchoUDPServerClient::onCustom(const string& type) throw (exception) {
	std::cout << "custom event '" << type << "' with '" << getIp() << ":" << getPort() << "'"<< endl;
}
