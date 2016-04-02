/**
 * @version $Id: 9292490a49dff82f0e222cd5daeac77323769a90 $
 */

#ifndef TDME_NETWORK_NIOTCPSERVERCLIENTFRAMING_H
#define TDME_NETWORK_NIOTCPSERVERCLIENTFRAMING_H

#include <string>
#include <queue>

#include <libtdme/network/shared/NIOTCPSocket.h>
#include <libtdme/network/shared/NIOIOException.h>

#include <libtdme/network/tcpserver/NIOTCPServerClient.h>
#include <libtdme/network/tcpserver/NIOTCPFramingException.h>

namespace TDMENetwork {

	using namespace std;

	class NIOTCPServerClient;

	/**
	 * @brief Client Framing interface
	 */
	class NIOTCPServerClientFraming {
		friend class NIOTCPServerClient;

		public:
			/**
			 * @brief public constructor
			 * @param client
			 */
			NIOTCPServerClientFraming(NIOTCPServerClient *client);

			/**
			 * @brief Reads frames from socket
			 * @throws NIOIOException
			 * @throws NIOTCPFramingException
			 */
			virtual void readFrame() throw (NIOIOException, NIOTCPFramingException) = 0;

			/**
			 * @brief Event, which will be called if frame has been received, defaults to NIOTCPServerClient::onFrameReceived()
			 * @param frame
			 */
			void onFrameReceived(stringstream* frame);

			/**
			 * @brief Write current out frame to socket
			 * @throws NIOIOException
			 * @return if the complete frame has successful been written
			 */
			bool writeFrame() throw (NIOIOException);

			/**
			 * @brief Pops the next frame to be written from output FIFO
			 * @return If a new frame has been available
			 */
			bool popWriteFrame();

			/**
			 * @brief Pushs a frame into output FIFO
			 * @param frame
			 * @throws NIOTCPFramingException
			 */
			virtual void pushWriteFrame(stringstream* frame) throw (NIOTCPFramingException);
		protected:
			/**
			 * @brief public destructor
			 * @param client
			 */
			virtual ~NIOTCPServerClientFraming();

			NIOTCPServerClient *client;
			NIOTCPSocket socket;

			typedef std::queue<stringstream*> OutFIFOQueue;
			stringstream* outFrame;
			OutFIFOQueue outFIFO;

			char buf[2048];
			size_t bufOffset;
			size_t bufLength;
	};


};

#endif
