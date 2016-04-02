/**
 * @version $Id: 9d8dfaef0d634c38ad446b419df31cc9f50a2c0a $
 */

#ifndef TDME_THREADING_THREADINGERROR_H
#define TDME_THREADING_THREADINGERROR_H

#include <string.h>
#include <sstream>

#include "../globals/Logger.h"

#define PTHREAD_CHECK_ERROR(NAME, MSG, FUNCTION) \
	if (result != 0) { \
		ostringstream msg; \
		msg << NAME; \
		msg << ": "; \
		msg << MSG; \
		msg << ", "; \
		msg << FUNCTION; \
		msg << " error '"; \
		msg << strerror(result); \
		msg << "' occured"; \
		TDMEGlobal::Logger::log(TDMEGlobal::Logger::LEVEL_FATAL, "%s", msg.str().c_str()); \
	}

#endif
