/**
 * @version $Id: 01311f2071d5dece2e11103fe5ed3b19c093f3d2 $
 */

#include <libtdme/globals/Logger.h>
#include <libtdme/network/shared/NIOServerWorkerThreadPool.h>

using namespace TDMENetwork;

NIOServerWorkerThreadPool::NIOServerWorkerThreadPool(Barrier* startUpBarrier, const unsigned int workerCount, const unsigned int maxElements) :
	Queue<NIOServerRequest>(maxElements),

	startUpBarrier(startUpBarrier),
	workerCount(workerCount),
	worker(NULL) {
	//
}

NIOServerWorkerThreadPool::~NIOServerWorkerThreadPool() {
}

void NIOServerWorkerThreadPool::start() {
	worker = new NIOServerWorkerThread*[workerCount];
	for(unsigned int i = 0; i < workerCount; i++) {
		worker[i] = new NIOServerWorkerThread(i, this);
		worker[i]->start();
	}
}

void NIOServerWorkerThreadPool::stop() {
	// stop queue
	Queue<NIOServerRequest>::stop();

	// stop worker
	for(unsigned int i = 0; i < workerCount; i++) {
		// wait until worker has finished
		worker[i]->join();
		// delete worker
		delete worker[i];
	}
	delete [] worker;
}
