/**
 * @version $Id: e13b1846e69caf30eca64284ddc50018ea6b2af0 $
 */

#include <libtdme/network/tcpserver/NIOTCPTelnetFraming.h>

#include <iostream>

using namespace std;
using namespace TDMENetwork;

NIOTCPTelnetFraming::NIOTCPTelnetFraming(NIOTCPServerClient* client): NIOTCPServerClientFraming(client), inFrame(new stringstream()) {
}

NIOTCPTelnetFraming::~NIOTCPTelnetFraming() {
	delete inFrame;
}

// read, write events
void NIOTCPTelnetFraming::readFrame() throw (NIOIOException, NIOTCPFramingException) {
	char inBuf[2048];
	size_t bytesRead = socket.read(inBuf, 2048);
	for (size_t i = 0; i < bytesRead; i++) {
		char c = inBuf[i];
		if (c == '\r') {
			// ignore
		} else
		if (c == '\n') {
			onFrameReceived(inFrame);
			inFrame = new stringstream();
		} else {
			if (inFrame->tellg() >= 1024) {
				throw NIOTCPFramingException("In frame too large");
			}
			*inFrame << c;
		}
	}
}

void NIOTCPTelnetFraming::pushWriteFrame(stringstream* frame) throw (NIOTCPFramingException) {
	// only allow a max of 20 frames in out fifo queue
	if (outFIFO.size() >= 20) {
		throw NIOTCPFramingException("Too many frames in out fifo");
	}
	*frame << "\n";
	NIOTCPServerClientFraming::pushWriteFrame(frame);
}
