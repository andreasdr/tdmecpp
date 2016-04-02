/**
 * @version $Id: dba01477c8a4656b922c27bbdf20c63d5e61cff7 $
 */

#ifndef TDME_THREADING_CONDITION_H
#define TDME_THREADING_CONDITION_H

#include <pthread.h>

#include <string>

#include "../globals/globals.h"
#include "Mutex.h"

using namespace std;

namespace TDMEThreading {

	/**
	 * Threading condition variable implementation
	 * @author Andreas Drewke
	 */
	class Condition {
		public:
			/**
			 * @brief Public constructor, creates condition variable
			 * @param string
			 */
			Condition(const string& name);

			/**
			 * @brief Destructor, removes condition variable
			 */
			~Condition();

			/**
			 * @brief wake ups a waiting thread on this condition, associated mutex should protect signal
			 */
			void signal();

			/**
			 * @brief wake ups all waiting threads on this condition, associated mutex should protect broadcast
			 */
			void broadcast();

			/**
			 * @brief Blocks current thread until signaled/broadcasted, associated mutex should protect wait
			 */
			void wait(Mutex &mutex);

		private:
			string name;
			pthread_cond_t pThreadCond;
	};

};

#endif
