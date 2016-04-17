/**
 * @version $Id: 636725e643c60e1f22906ce54f083c29333e90e9 $
 */

#include <stdio.h>

#include "ProducerThread.h"

using namespace ThreadingTestApp;

ProducerThread::ProducerThread(int id, TDMEThreading::Queue<int> *queue) : TDMEThreading::Thread("producer"), id(id), queue(queue) {
}

void ProducerThread::run() {
	printf("ProducerThread[%i]::run()\n", id);
	for(int i = 0; isStopRequested() == false; i++) {
		int* element = new int;
		*element = i;
		queue->addElement(element, false);
		printf("ProducerThread[%i]: added %i to queue\n", id, i);
		Thread::sleep(50);
	}
	printf("ProducerThread[%i]::done()\n", id);
}
