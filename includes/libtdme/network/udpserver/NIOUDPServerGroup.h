/**
 * @version $Id: 4b5d1c434368f3d81f57fa95c5c0545b8f4a3a11 $
 */

#ifndef TDME_NETWORK_NIOUDPSERVERGROUP
#define TDME_NETWORK_NIOUDPSERVERGROUP

#include <libtdme/network/shared/NIOServerGroup.h>

namespace TDMENetwork {

	using namespace TDMEThreading;

	class NIOUDPServerClient;

	/**
	 * Base class for NIO udp servers
	 * @author Andreas Drewke
	 */
	class NIOUDPServerGroup : public NIOServerGroup<NIOUDPServer, NIOUDPServerClient> {
		public:
			/**
			 * @brief Creates a frame to be used with send
			 * @return frame to be send
			 */
			// stringstream* createFrame();

			/**
			 * @brief Sends a frame to client, takes over ownership of frame
			 * @param frame data
			 * @param safe, requires ack and retransmission
			 */
			// void send(stringstream* frame, bool safe = true);
	};

};

#endif
