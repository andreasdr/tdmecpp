/**
 * @version $Id: 0803c07bc8c0b9ca13572da27f6de09ed050375f $
 */

#include <libtdme/network/tcpserver/NIOTCPFLIFraming.h>

#ifdef __APPLE__
	#include <CoreFoundation/CoreFoundation.h>
	#define htole32(x) CFSwapInt32HostToLittle(x)
	#define le32toh(x) CFSwapInt32LittleToHost(x)
#endif

#include <iostream>

using namespace std;
using namespace TDMENetwork;

NIOTCPFLIFraming::NIOTCPFLIFraming(NIOTCPServerClient* client): NIOTCPServerClientFraming(client), readMode(READMODE_SIZE), inFrameSize(0), inFrame(new stringstream()) {
}

NIOTCPFLIFraming::~NIOTCPFLIFraming() {
	delete inFrame;
}

// read, write events
void NIOTCPFLIFraming::readFrame() throw (NIOIOException, NIOTCPFramingException) {
	char inBuf[2048];
	size_t inBufOffset = 0;
	size_t bytesRead = socket.read(inBuf, 2048);
	while (true == true) {
		switch (readMode) {
			case READMODE_SIZE: {
				// read as much as possible
				size_t bytesToRead = 4 - inFrame->tellp();
				size_t bytesReadable = bytesRead - inBufOffset;
				bytesToRead = bytesReadable < bytesToRead?bytesReadable:bytesToRead;
				inFrame->write(
					&inBuf[inBufOffset],
					bytesToRead
				);
				inBufOffset+= bytesToRead;
				// check if size was given
				if (inFrame->tellp() == 4) {
					// read size
					uint32_t _inFrameSize;
					inFrame->read((char*)&_inFrameSize, 4);
					// convert it to host endian from little endian
					inFrameSize = le32toh(_inFrameSize);
					// check if valid
					if (inFrameSize == 0 || inFrameSize > 4096) {
						throw NIOTCPFramingException("NIOTCPFLIFraming::readFrame(): frame size invalid");
					}
					readMode = READMODE_CONTENT;

					// reset inframe
					delete inFrame;
					inFrame = new stringstream();
				}
				break;
			}
			case READMODE_CONTENT: {
				// read as much as possible
				size_t bytesToRead = inFrameSize - inFrame->tellp();
				size_t bytesReadable = bytesRead - inBufOffset;
				bytesToRead = bytesReadable < bytesToRead?bytesReadable:bytesToRead;
				inFrame->write(
					&inBuf[inBufOffset],
					bytesToRead
				);
				inBufOffset+= bytesToRead;
				// check if content was delivered completely
				if (inFrame->tellp() == inFrameSize) {
					// reset frame information
					inFrameSize = 0;
					readMode = READMODE_SIZE;
					onFrameReceived(inFrame);
					inFrame = new stringstream();
				}
				break;
			}
		}

		// exit if all data was processed
		if (inBufOffset == bytesRead) {
			return;
		}
	}
}

void NIOTCPFLIFraming::pushWriteFrame(stringstream* frame) throw (NIOTCPFramingException) {
	// only allow a max of 20 frames in out fifo queue
	if (outFIFO.size() >= 20) {
		throw NIOTCPFramingException("NIOTCPFLIFraming::pushWriteFrame(): Too many frames in out fifo");
	}
	// create size frame
	stringstream* size = new stringstream();
	uint32_t intSize = htole32(frame->tellp());
	size->write((char*)&intSize, 4);
	// push frame size
	NIOTCPServerClientFraming::pushWriteFrame(size);
	// push frame content
	NIOTCPServerClientFraming::pushWriteFrame(frame);
}
