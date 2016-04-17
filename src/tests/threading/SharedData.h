/**
 * @version $Id: ebdf2bbe743139b199f9202fccae9c14d885747b $
 */

#ifndef THREADINGTEST_SHAREDDATA_H 
#define THREADINGTEST_SHAREDDATA_H

#include <libtdme/globals/globals.h>
#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Mutex.h>

namespace ThreadingTestApp {

	class SharedData {
		public:
			SharedData() : m("shareddata"), counter(0) { };
			inline void incrementCounter() { m.lock(); int i = counter; counter = i + 1; m.unlock(); };
			inline int getCounter() { return counter; };
		private:
			TDMEThreading::Mutex m;
			int counter;
	};
};

#endif 
