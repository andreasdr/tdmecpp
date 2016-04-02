/**
 * @version $Id: 73a60f6584e0f5b5e4fc1919a5cc6a7d1bc262b3 $
 */

#ifndef TDME_THREADING_MUTEX_H
#define TDME_THREADING_MUTEX_H 

#include <pthread.h>

#include <string>

#include "../globals/globals.h"

using namespace std;

namespace TDMEThreading {

	/**
	 * Mutex implementation.
	 * Mutexes are used to ensure that only one process can run a critical section,
	 * which is e.g. modifying shared data between thread.
	 * @author Andreas Drewke
	 */
	class Mutex {
		friend class Condition;

		public:
			/**
			 * @brief Public constructor
			 * @param name
			 */
			Mutex(const string& name);

			/**
			 * @brief Destroys the mutex
			 */
			~Mutex();

			/**
			 * @brief Locks the mutex, additionally mutex locks will block until other locks have been unlocked.
			 */
			void lock();

			/**
			 * @brief Unlocks this mutex
			 */
			void unlock();

		private:
			string name;
			pthread_mutex_t pThreadMutex;
	};

};

#endif
