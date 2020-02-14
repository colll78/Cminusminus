#include "JMMLogger.h"


log_level logger::_threshold_level = LOG_ERROR;

log_level& logger::threshold_level(){
	return _threshold_level;
}

