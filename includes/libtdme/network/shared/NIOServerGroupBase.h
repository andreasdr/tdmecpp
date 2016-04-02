/**
 * @version $Id: ade35546489408ef4db41c12d81c98342e917f11 $
 */

#ifndef TDME_NETWORK_NIOSERVERGROUPEVENTS
#define TDME_NETWORK_NIOSERVERGROUPEVENTS

#include <stdint.h>

#include <exception>
#include <string>
#include <sstream>

#include <libtdme/globals/ReferenceCounter.h>

namespace TDMENetwork {

	using namespace std;
	using namespace TDMEGlobal;

	/**
	 * Base class for NIO server groups events
	 * @author Andreas Drewke
 	 */
	class NIOServerGroupBase : public ReferenceCounter {
		friend class NIOServerWorkerThread;

		protected:
			/*
			 * @brief event method called if group will be initiated, will be called from worker
			 */
			virtual void onInit() throw (exception) = 0;

			/*
			 * @brief event method called if client will be closed, will be called from worker
			 */
			virtual void onClose() throw (exception) = 0;

			/*
			 * @brief custom event method called if fired, will be called from worker
			 */
			virtual void onCustomEvent(const string& type) throw (exception) = 0;
	};

};

#endif
