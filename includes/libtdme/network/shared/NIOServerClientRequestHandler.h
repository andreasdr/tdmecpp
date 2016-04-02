/**
 * @version $Id: 5e72af1aed53c144d586620ff6f88f9c94ff1542 $
 */

#ifndef TDME_NETWORK_NIOSERVERCLIENTREQUESTHANDLER_H_
#define TDME_NETWORK_NIOSERVERCLIENTREQUESTHANDLER_H_

#include <stdint.h>

#include <exception>
#include <string>

namespace TDMENetwork {

	using namespace std;

	/**
	 * @brief Client request handler base class
	 * @author Andreas Drewke
	 */
	template <class CLIENT, class REQUEST>
	class NIOServerClientRequestHandler {
		public:
			/**
			 * @brief Public constructor
			 */
			NIOServerClientRequestHandler(const std::string& command) {
				this->command = command;
			}

			/**
			 * @brief Public destructor
			 */
			virtual ~NIOServerClientRequestHandler() {
			}

			/**
			 * @brief Returns this requests handler command name
			 */
			const string& getCommand() {
				return command;
			}

			/**
			 * @brief Request handler implementation
			 * @param client
			 * @param request data
			 * @param message id (udp server only)
			 * @param retries (udp server only)
			 */
			virtual void handleRequest(CLIENT* client, REQUEST& request, const uint32_t messageId, const uint8_t retries) throw (exception) = 0;
		private:
			string command;
	};

};

#endif
