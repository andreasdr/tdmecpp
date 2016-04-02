/**
 * @version $Id: 1005ee404957a6543d496d54426b1523fe4ac54d $
 */

#include <cstdarg>
#include <stdio.h>
#include <iostream>
#include <libtdme/globals/Logger.h>
#include <libtdme/globals/Time.h>

using namespace TDMEGlobal;
using namespace std;

// initialize static variables
Logger::Level Logger::logLevel = LEVEL_INFO;
TDMEThreading::Mutex Logger::mutex("logger");

void Logger::setLevel(const Level level) {
	logLevel = level;
}

void Logger::log(const Level level, const char* format, ...) {
	// skip on lower level than our log level
	if (level < logLevel) {
		return;
	}

	char buf[1024];

	va_list arguments;
	va_start(arguments, format);
	vsnprintf(buf, 1024, format, arguments);
	va_end(arguments);

	// do it serialized, FIXME: should use LoggerThread and consumer producer queue to avoid locking
	mutex.lock();
	cout << Time::getTimestamp() << "|" << buf << endl;
	mutex.unlock();
}
