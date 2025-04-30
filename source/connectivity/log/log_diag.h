#ifndef LOG_DIAG_H
#define LOG_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "log_constants.h"

#ifndef HAS_LOG_DIAG
#error "+ HAS_LOG_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_LOG
#error "+  HAS_LOG"
#endif

facility_t str2facility(const char* const str);
const char* log_level_name_long(log_level_t level);
bool log_level_diag(const char* const keyWord1);
char log_level_name(log_level_t level);
const char* log_level_color(log_level_t level);
log_level_t str2level(const char* str);

#ifdef __cplusplus
}
#endif

#endif /* LOG_DIAG_H */
