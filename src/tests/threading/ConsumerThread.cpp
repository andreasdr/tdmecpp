/**
 * @version $Id: 5d6a0c979e82e4789714d75918e47b11b19459a9 $
 */

#include <stdio.h>

#include "ConsumerThread.h"

using namespace ThreadingTestApp;

ConsumerThread::ConsumerThread(int id, TDMEThreading::Queue<int> *queue) : TDMEThreading::Thread("consumer"), id(id), queue(queue) {
}

void ConsumerThread::run() {
	printf("ConsumerThread[%i]::run()\n", id);
	while(isStopRequested() == false) {
		int* element = queue->getElement();
		if (element == NULL) {
			break;
		}
		printf("ConsumerThread[%i]: got %i from queue\n", id, *element);
		Thread::sleep(100);
	}
	printf("ConsumerThread[%i]::done()\n", id);
}
