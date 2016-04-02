/**
 * @version $Id: c8d7a409d0ec9b6e8c540ab690a5b0bec8961f16 $
 */

#ifndef TDME_NETWORK_NIOTCPFLFRAMING_H
#define TDME_NETWORK_NIOTCPFLFRAMING_H

#include <sstream>

#include <libtdme/network/tcpserver/NIOTCPServerClientFraming.h>
#include <libtdme/network/tcpserver/NIOTCPFramingException.h>

namespace TDMENetwork {

	using namespace std;

	/**
	 * @brief Frame length information framing implementation
	 * @author Andreas Drewke
	 */
	class NIOTCPFLIFraming : public NIOTCPServerClientFraming {
		public:
			/**
			 * @brief Public constructor
			 */
			NIOTCPFLIFraming(NIOTCPServerClient* client);

			/**
			 * @brief Reads a frame
			 * @throws NIOIOException
			 * @throws NIOTCPFramingException
			 */
			void readFrame() throw (NIOIOException, NIOTCPFramingException);

			/**
			 * @brief Pushs a frame into output FIFO, takes over ownership of "frame"
			 * @param frame
			 * @throws NIOTCPFramingException
			 */
			virtual void pushWriteFrame(stringstream* frame) throw (NIOTCPFramingException);
		protected:
			enum ReadMode {
				READMODE_SIZE,
				READMODE_CONTENT
			};

			/**
			 * @brief Protected destructor
			 */
			virtual ~NIOTCPFLIFraming();

		private:
			ReadMode readMode;
			uint32_t inFrameSize;
			stringstream* inFrame;
	};

};

#endif
