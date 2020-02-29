#pragma once
#include <stdarg.h>
#include <stdio.h>

enum log_level { LOG_DEBUG, LOG_DEBUG1, LOG_DEBUG2, LOG_DEBUG3, LOG_DEBUG4, LOG_INFO, LOG_WARNING, LOG_ERROR };

class logger {
public:
	static log_level& threshold_level();
	template<log_level msg_lvl> static void log(const char* format, ...) {
		if (msg_lvl >= _threshold_level) {
			va_list args;
			int done;
			va_start(args, format);
			done = vfprintf(stderr, format, args);
			va_end(args);
		}
	}
	template<log_level msg_lvl> static void slog(const char* format, ...) {
		if (msg_lvl == _threshold_level) {
			va_list args;
			int done;
			va_start(args, format);
			done = vfprintf(stderr, format, args);
			va_end(args);
		}
	}
	static log_level _threshold_level;
};