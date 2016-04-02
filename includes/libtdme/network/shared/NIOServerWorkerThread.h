/**
 * @version $Id: cbdc31a00b51455af67b8e482e66b554baee7dff $
 */

#ifndef NIOSERVERWORKERTHREAD_H_
#define NIOSERVERWORKERTHREAD_H_

#include <stdint.h>

#include <libtdme/threading/Thread.h>
#include "NIOServerWorkerThreadPool.h"

namespace TDMENetwork {

	class NIOServerWorkerThreadPool;

	using namespace TDMEThreading;

	/**
	 * @brief Server worker thread
	 * @author Andreas Drewke
	 */
	class NIOServerWorkerThread : public Thread {
		public:
			/**
			 * @brief Public constructor
			 * @param id
			 * @param thread pool
			 */
			NIOServerWorkerThread(const unsigned int id, NIOServerWorkerThreadPool* threadPool);

			/**
			 * @brief Public destructor
			 */
			virtual ~NIOServerWorkerThread();

			/**
			 * @brief Thread run method
			 */
			void run();
		private:
			unsigned int id;
			NIOServerWorkerThreadPool *threadPool;
	};

}

#endif
