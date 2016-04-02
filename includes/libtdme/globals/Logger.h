/**
 * @version $Id: 3382b391535546708970ce5e279706a037271a5d $
 */

#ifndef TDME_GLOBAL_LOGGER_H
#define TDME_GLOBAL_LOGGER_H

#include "../threading/Mutex.h"

namespace TDMEGlobal {

	using namespace std;

	/**
	 * Easy logger implementation
	 * @author Andreas Drewke
	 */
	class Logger {
		public:
			enum Level {LEVEL_FATAL = 4, LEVEL_ERROR = 3, LEVEL_WARNING = 2, LEVEL_INFO = 1, LEVEL_FUNCTION = 0};

			/**
			 * @brief set up log level
			 * @param level
			 */
			static void setLevel(const Level level);

			/**
			 * @brief printf style like logging
			 * @param log level
			 * @param format
			 * @param ..
			 */
			static void log(const Level level, const char* format, ...);
		private:
			static Level logLevel;
			static TDMEThreading::Mutex mutex;
	};

};

#endif
