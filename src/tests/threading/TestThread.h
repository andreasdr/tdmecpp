/**
 * @version $Id: 2d1b8d1b064bf3afa4dd5da2000cde92e8bbaef3 $
 */

#ifndef THREADINGTEST_TESTTHREAD_H
#define THREADINGTEST_TESTTHREAD_H

#include <libtdme/globals/globals.h>
#include <libtdme/threading/Thread.h>

#include "SharedData.h"

namespace ThreadingTestApp {

	class TestThread : public TDMEThreading::Thread {
		public:
			TestThread(int id, SharedData *data);
			void run();
		private:
			int id;
			SharedData *data;
	};
};

#endif 
