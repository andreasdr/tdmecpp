/**
 * @version $Id: 60613947c48eae23aa19b72de5fdeb3beafc2f20 $
 */

#ifndef TDME_THREADING_THREAD_H
#define TDME_THREADING_THREAD_H

#include <pthread.h>

#include <string>

#include "../globals/globals.h"

using namespace std;

namespace TDMEThreading {

	/**
	 * Base class for threads.
	 * @author Andreas Drewke
	 */
	class Thread {
		public:
			/**
			 * @brief Public constructor
			 */
			Thread(const string& name);

			/**
			 * @brief Public destructor
			 */
			virtual ~Thread();

			/**
			 * @brief sleeps current thread for given time in milliseconds
			 * @param uint64_t milliseconds to wait
			 */
			static void sleep(const uint64_t milliseconds);

			/**
			 * @brief Blocks caller thread until this thread has been terminated
			 */
			void join();

			/**
			 * @brief Starts this objects thread
			 */
			void start();

			/**
			 * @brief Abstract run() method, should be implemented by subclassed class, will be called after spawn by start()
			 */
			virtual void run() = 0;

			/**
			 * @brief Requests that this thread should be stopped
			 */
			void stop();

			/**
			 * @brief Returns if stop has been requested
			 * @return bool
			 */
			bool isStopRequested();
		private:
			static void *pThreadRun(void *thread);

			string name;
			bool pThreadCreated;
			pthread_t pThread;
			volatile bool stopRequested;
	};

};

#endif
