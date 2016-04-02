/**
 * @version $Id: a1c555ad959edf8412e381e1af34dae9649bab54 $
 */

#ifndef TDME_THREADING_BARRIER_H
#define TDME_THREADING_BARRIER_H

#include <pthread.h>

#include <string>

#include "../globals/globals.h"
#include "Mutex.h"
#include "Condition.h"

using namespace std;

namespace TDMEThreading {

	/**
	 * Barrier implementation.
	 * @author Andreas Drewke
	 */
	class Barrier {
		public:
			/**
			 * @brief Public constructor
			 * @param name
			 * @param Number of threads that need to "wait" on barrier to complete barrier
			 */
			Barrier(const string& name, const unsigned int count);

			/**
			 * @brief Destroys the barrier
			 */
			~Barrier();

			/**
			 * @brief Waits on barrier
			 * @return bool if caller thread is selected for updating shared data
			 */
			bool wait();
		private:
			string name;
			unsigned int count;
			unsigned int entered;
			volatile unsigned int exited;
			Mutex m;
			Condition c;
	};

};

#endif
