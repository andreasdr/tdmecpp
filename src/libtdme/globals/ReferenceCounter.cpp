/**
 * @version $Id: d356efc86319b872b76fbb6fca1433cb987a9398 $
 */

#include <libtdme/globals/ReferenceCounter.h>

using namespace TDMEGlobal;

ReferenceCounter::ReferenceCounter() : referenceCounter(0) {
}

ReferenceCounter::~ReferenceCounter() {
}

void ReferenceCounter::acquireReference() {
	// atomic add
	__sync_add_and_fetch(&referenceCounter, 1);
}

void ReferenceCounter::releaseReference() {
	// atomic dec and check if zero
	if (__sync_sub_and_fetch(&referenceCounter, 1) == 0) {
		// yep, no more references, delete object
		delete this;
	}
}

