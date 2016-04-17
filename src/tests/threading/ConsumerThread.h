/**
 * @version $Id: 2c20f6cff38a9fbcd088eddcef51e9217c65f6ef $
 */

#ifndef THREADINGTEST_CONSUMERTHREAD_H 
#define THREADINGTEST_CONSUMERTHREAD_H 

#include <libtdme/globals/globals.h>
#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Queue.h>

namespace ThreadingTestApp {

	class ConsumerThread: public TDMEThreading::Thread {
		public:
			ConsumerThread(int id, TDMEThreading::Queue<int> *queue);
			void run();
		private:
			int id;
			TDMEThreading::Queue<int> *queue;
	};
};

#endif 
