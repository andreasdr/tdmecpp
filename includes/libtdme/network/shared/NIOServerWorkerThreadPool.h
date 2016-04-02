/**
 * @version $Id: 84451e09c9da26269b28e4484ea0805460086760 $
 */

#ifndef NIOSERVERWORKERTHREADPOOL_H_
#define NIOSERVERWORKERTHREADPOOL_H_

#include <libtdme/threading/Barrier.h>
#include <libtdme/threading/Queue.h>

#include <libtdme/network/shared/NIOServerRequest.h>

#include "NIOServerWorkerThread.h"

namespace TDMENetwork {

	class NIOServerWorkerThread;
	class NIOServerRequest;

	using namespace TDMEThreading;

	/**
	 * @brief Simple server worker thread pool class
	 * @author Andreas Drewke
	 */
	class NIOServerWorkerThreadPool : public Queue<NIOServerRequest> {
		friend class NIOServerWorkerThread;

		public:

			/**
			 * @brief Public constructor
			 * @param server
			 * @param worker count
			 */
			NIOServerWorkerThreadPool(Barrier* startUpBarrier, const unsigned int workerCount, const unsigned int maxElements);

			/**
			 * @brief Public destructor
			 */
			virtual ~NIOServerWorkerThreadPool();

			/**
			 * @brief Start worker thread pool
			 */
			void start();

			/**
			 * @brief Stop worker thread pool
			 */
			void stop();
		private:
			Barrier* startUpBarrier;
			unsigned int workerCount;
			NIOServerWorkerThread** worker;
	};

};

#endif
