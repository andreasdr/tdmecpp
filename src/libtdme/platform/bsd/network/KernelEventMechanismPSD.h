/**
 * @version $Id: 2bdc3814c90ab98569704a875c6debe62b462186 $
 */

#ifndef TDME_NETWORK_KERNELEVENTMECHANISMPSD_H
#define TDME_NETWORK_KERNELEVENTMECHANISMPSD_H

#include <sys/event.h>

#include <libtdme/threading/Mutex.h>

namespace TDMENetwork {

	class KernelEventMechanism;

	/**
	 * BSD kernel event mechanism platform specific data
	 * @author Andreas Drewke
	 */
	class KernelEventMechanismPSD {
		friend class KernelEventMechanism;

		private:
			/**
			 * @brief Public constructor
			 */
			KernelEventMechanismPSD() :
				kq(0),
				kqChangeListMax(0),
				kqChangeListBuffer(0),
				kqChangeListCurrent(0),
				kqChangeList(NULL),
				kqMutex("kem_kq_mutex"),
				kqEventListMax(0),
				kqEventList(NULL) {
				//
			}

			int kq;

			unsigned int kqChangeListMax;
			unsigned int kqChangeListBuffer;
			unsigned int kqChangeListCurrent;
			struct kevent** kqChangeList;
			TDMEThreading::Mutex kqMutex;

			unsigned int kqEventListMax;
			struct kevent* kqEventList;
	};

};

#endif
