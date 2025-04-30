#ifndef LOG_GENERAL_CONSTANTS_H
#define LOG_GENERAL_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_SYSTEM
#include "sys_constants.h"
#endif

#include "terminal_codes.h"
#include "log_dep.h"

#define LOG_OK "Ok!"
#define LOG_ER "Err"
#define CRLF "\r\n"
#define LF "\n"
#define LFCR "\n\r"
#define BEEP "\a"
#define CARRIAGE_RETURN 0x0D // or '\r'
#define LINE_FEED 0x0A       // or '\n'

typedef enum {
    LOG_LEVEL_UNKNOWN = -5,
    LOG_LEVEL_PARANOID = -4,
    LOG_LEVEL_DEBUG = -3,
    LOG_LEVEL_PROTECTED = -2,
    LOG_LEVEL_NOTICE = -1,
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_WARNING = 1,
    LOG_LEVEL_ERROR = 2,
    LOG_LEVEL_CRITICAL = 3,
    LOG_LEVEL_LAST = LOG_LEVEL_CRITICAL
} log_level_t;

#ifdef __cplusplus
}
#endif

#endif /* LOG_GENERAL_CONSTANTS_H */
