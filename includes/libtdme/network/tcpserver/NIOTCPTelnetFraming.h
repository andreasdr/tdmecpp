/**
 * @version $Id: 5707d381573aa4d3bb17bbb817c7aa4f92b4233f $
 */

#ifndef TDME_NETWORK_NIOTCPTELNETFRAMING_H
#define TDME_NETWORK_NIOTCPTELNETFRAMING_H

#include <sstream>

#include "NIOTCPServerClientFraming.h"
#include "NIOTCPFramingException.h"

namespace TDMENetwork {

	using namespace std;

	/**
	 * @brief Telnet framing implementation
	 * @author Andreas Drewke
	 */
	class NIOTCPTelnetFraming : public NIOTCPServerClientFraming {
		public:
			/**
			 * @brief Public constructor
			 */
			NIOTCPTelnetFraming(NIOTCPServerClient* client);

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
			/**
			 * @brief Protected destructor
			 */
			virtual ~NIOTCPTelnetFraming();

		private:
			stringstream* inFrame;
	};

};

#endif
