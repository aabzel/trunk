#ifndef LOG_DIAG_H
#define LOG_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "log_constants.h"
#include "log_types.h"

#ifndef HAS_LOG_DIAG
#error "+ HAS_LOG_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_LOG
#error "+  HAS_LOG"
#endif

bool log_level_diag(const char* const keyWord1);
char log_level_name(const log_level_t level);
const char* LogLevelToStr(const LogLevels_t LogLevels);
const char* log_res_to_color(const bool res);
const char* log_level_name_long(log_level_t level);
const char* LogEndOfLineToStr(LogEndOfLine_t eof);
const char* log_level_color(log_level_t level);
facility_t strToFacility(const char* const str);
log_level_t strToLogLevel(const char* const str);

#ifdef __cplusplus
}
#endif

#endif /* LOG_DIAG_H */
