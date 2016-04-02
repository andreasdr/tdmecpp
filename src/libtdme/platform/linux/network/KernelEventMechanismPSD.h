/**
 * @version $Id: e2863365eafe7b7aea2b39eb630155e3555f0a36 $
 */

#ifndef TDME_NETWORK_KERNELEVENTMECHANISMPSD_H
#define TDME_NETWORK_KERNELEVENTMECHANISMPSD_H

#include <sys/epoll.h>

namespace TDMENetwork {

	class KernelEventMechanism;

	/**
	 * linux kernel event mechanism platform specific data
	 * @author Andreas Drewke
	 */
	class KernelEventMechanismPSD {
		friend class KernelEventMechanism;

		private:
			/**
			 * @brief Public constructor
			 */
			KernelEventMechanismPSD() :
				ep(0),
				epEventListMax(0),
				epEventList(NULL) {
				//
			}

			int ep;
			unsigned int epEventListMax;
			struct epoll_event* epEventList;
	};

};

#endif
