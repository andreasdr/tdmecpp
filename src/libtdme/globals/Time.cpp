/**
 * @version $Id: 5e1ab15881f7ed322867e610208dc72b5be2a5f0 $
 */

#include <sys/time.h>

#include <libtdme/globals/Time.h>

using namespace TDMEGlobal;
using namespace std;

uint64_t Time::getTimestamp() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
