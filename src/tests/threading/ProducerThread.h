/**
 * @version $Id: c3f220a4422b068e3b2456dfd52bde84db0b7ace $
 */

#ifndef THREADINGTEST_PRODUCERTHREAD_H
#define THREADINGTEST_PRODUCERTHREAD_H

#include <libtdme/globals/globals.h>
#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Queue.h>

namespace ThreadingTestApp {

	class ProducerThread: public TDMEThreading::Thread {
		public:
			ProducerThread(int id, TDMEThreading::Queue<int> *queue);
			void run();
		private:
			int id;
			TDMEThreading::Queue<int> *queue;
	};
};

#endif 
