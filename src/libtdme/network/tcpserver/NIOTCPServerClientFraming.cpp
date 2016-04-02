/**
 * @version $Id: 60b1bccc442f31b1087a866c1a6bf088e43b0c96 $
 */

#include <libtdme/network/tcpserver/NIOTCPServerClientFraming.h>

using namespace std;
using namespace TDMENetwork;

NIOTCPServerClientFraming::NIOTCPServerClientFraming(NIOTCPServerClient *client) :
	client(client),
	socket(client->socket),
	outFrame(NULL),
	bufOffset(0),
	bufLength(0) {
}

NIOTCPServerClientFraming::~NIOTCPServerClientFraming() {
	// delete current out frame
	if (outFrame != NULL) {
		delete outFrame;
	}

	// delete remaining out frames
	while (outFIFO.size() > 0) {
		// fetch element
		stringstream* outFrame = outFIFO.front();
		// delete element
		delete outFrame;
		// delete element from queue
		outFIFO.pop();
	}
}

void NIOTCPServerClientFraming::onFrameReceived(stringstream* frame) {
	// delegate frame to client
	client->onFrameReceived(frame);
}

bool NIOTCPServerClientFraming::writeFrame() throw (NIOIOException) {
	while (outFrame != NULL) {
		// check if we need to fill the buffer
		if (bufOffset == bufLength) {
			size_t leftBytes = outFrame->tellp() - outFrame->tellg();
			if (leftBytes == 0) {
				// release outFrame
				delete outFrame;
				outFrame = NULL;
				// we've send the whole frame
				return true;
			}
			// fill buffer to be send
			bufLength = leftBytes > 2048?2048:leftBytes;
			bufOffset = 0;
			outFrame->read(buf, bufLength);
		}
		// try to send buffer
		while(bufOffset < bufLength) {
			// try to write remaining data
			size_t written = socket.write((void*)(&buf[bufOffset]), bufLength - bufOffset);
			// write would have blocked
			if (written == 0) {
				// so try on next event
				return false;
			}
			// 
			bufOffset+= written;
		}
	}
	return true;
}

bool NIOTCPServerClientFraming::popWriteFrame() {
	outFrame = NULL;
	if (outFIFO.empty() == false) {
		outFrame = outFIFO.front();
		outFIFO.pop();
		return true;
	} else {
		return false;
	}
}

void NIOTCPServerClientFraming::pushWriteFrame(stringstream* frame)  throw (NIOTCPFramingException) {
	outFIFO.push(frame);
}
