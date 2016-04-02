/**
 * @version $Id: 0c1dc743f2bd6b1c64a970e66d57837e1e023bdf $
 */

#ifndef TDME_NETWORK_KERNELEVENTMECHANISM_H
#define TDME_NETWORK_KERNELEVENTMECHANISM_H

#include "NIOInterest.h"
#include "NIONetworkSocket.h"
#include "NIOKEMException.h"

namespace TDMENetwork {

	/**
	 * Interface to kernel event mechanismns
	 * @author Andreas Drewke
	 */
	class KernelEventMechanism {
		public:
			/**
			 * @brief Public constructor
			 * @throws NIOKEMException
			 */
			KernelEventMechanism() throw (NIOKEMException);

			/**
			 * @brief destructor
			 */
			~KernelEventMechanism();

			/**
			 * @brief initializes the kernel event mechanism
			 * @param supported max ccu
			 * @throws NIOKEMException
			 */
			void initKernelEventMechanism(const unsigned int maxCCU)  throw (NIOKEMException);

			/**
			 * @brief shutdowns the kernel event mechanism
			 */
			void shutdownKernelEventMechanism();

			/**
			 * @brief do the kernel event mechanism
			 * @return number of events
			 * @throws NIOKEMException
			 */
			int doKernelEventMechanism() throw (NIOKEMException);

			/**
			 * @brief decodes a kernel event
			 * @param kernel event index
			 * @param kernel event io interest
			 * @param kernel event cookie
			 * @throws NIOKEMException
			 */
			void decodeKernelEvent(const unsigned int index, NIOInterest &interest, void*& cookie) throw (NIOKEMException);

			/**
			 * @brief sets a non blocked socket io interest
			 * @param socket
			 * @param last nio interest
			 * @param nio interest
			 * @param cookie
			 * @throws NIOKEMException
			 */
			void setSocketInterest(const NIONetworkSocket &socket, const NIOInterest lastInterest, const NIOInterest interest, const void* cookie) throw (NIOKEMException);

		private:
			//
			bool initialized;

			// platform specific data
			void* _psd;
	};

};

#endif
