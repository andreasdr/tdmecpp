/**
 * @version $Id: 1a286d86b29cabf8420205519e524a885c74a8d7 $
 */

#include <libtdme/threading/Mutex.h>
#include <libtdme/threading/ThreadingError.h>

using namespace TDMEThreading;
using namespace TDMEGlobal;

Mutex::Mutex(const string& name) {
	this->name = name;
	int result = pthread_mutex_init(&pThreadMutex, NULL);
	PTHREAD_CHECK_ERROR(name, "Could not init mutex", "pthread_mutex_init");
}

Mutex::~Mutex() {
	int result = pthread_mutex_destroy(&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, "Could not destroy mutex", "pthread_mutex_destroy");
}

void Mutex::lock() {
	int result = pthread_mutex_lock(&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, "Could not lock mutex", "pthread_mutex_lock");
}

void Mutex::unlock() {
	int result = pthread_mutex_unlock (&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, "Could not unlock mutex", "pthread_mutex_unlock");
}
