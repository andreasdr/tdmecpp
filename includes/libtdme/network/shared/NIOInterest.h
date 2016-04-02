/**
 * @version $Id: 8b1b6422d42f3a55b4aee31ab588debf1416cd3b $
 */

#ifndef TDME_NETWORK_NIOINTEREST
#define TDME_NETWORK_NIOINTEREST

#include <libtdme/globals/globals.h>

namespace TDMENetwork {

	/**
	 * @brief type definiton for io interest, see NIONetworkServerClient::INTEREST_*
	 */
	typedef uint8_t NIOInterest;
	const NIOInterest NIO_INTEREST_NONE = 0;
	const NIOInterest NIO_INTEREST_READ = 1;
	const NIOInterest NIO_INTEREST_WRITE = 2;

};

#endif
