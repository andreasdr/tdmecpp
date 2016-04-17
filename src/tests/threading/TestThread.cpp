/**
 * @version $Id: 3b47d6b98dcd02a2676d3d3cd320ab1cba927aee $
 */

#include <stdio.h>

#include "TestThread.h"

using namespace ThreadingTestApp;

TestThread::TestThread(int id, SharedData *data) : TDMEThreading::Thread("test"), id(id), data(data) {
}

void TestThread::run() {
	printf("TestThread::run()\n");
	for(int i = 0; i < 100; i++) {
		printf("%i:%i\n", id, data->getCounter());
		data->incrementCounter();
	}
}
