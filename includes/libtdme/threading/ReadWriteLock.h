/**
 * @version $Id: 5a0c15f315579d2ff415e5781432f74f006e6f5f $
 */

#ifndef TDME_THREADING_READWRITELOCK_H
#define TDME_THREADING_READWRITELOCK_H

#include <pthread.h>

#include <string>

#include "../globals/globals.h"

using namespace std;

namespace TDMEThreading {

	/**
	 * Implementation for read/write lock
	 * @author Andreas Drewke
	 */
	class ReadWriteLock {
		public:
			/**
			 * @brief Public constructor
			 * @param name
			 */
			ReadWriteLock(const string& name);

			/**
			 * @brief Destroys the read write lock
			 */
			~ReadWriteLock();

			/**
			 * @brief Locks for reading / shared lock
			 */
			void readLock();

			/**
			 * @brief Locks for writing / exclusive lock
			 */
			void writeLock();

			/**
			 * @brief Unlocks this read write lock
			 */
			void unlock();
		private:
			string name;
			pthread_rwlock_t pReadWriteLock;
	};

};

#endif
