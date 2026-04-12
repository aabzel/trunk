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

// or '\r'
#define CARRIAGE_RETURN (0x0d)
// or '\n'
#define LINE_FEED 0x0A

typedef enum {
    LOG_EOF_UNDEF = 0,
    LOG_EOF_CRLF  = 1,
    LOG_EOF_CR    = 2,
    LOG_EOF_LF    = 3,
    LOG_EOF_LFCR  = 4,
} LogEndOfLine_t;

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
    LOG_LEVEL_COVERAGE = 4,
    LOG_LEVEL_DISABLE = 5,
    LOG_LEVEL_LAST = LOG_LEVEL_DISABLE
} log_level_t;

#ifdef __cplusplus
}
#endif

#endif /* LOG_GENERAL_CONSTANTS_H */
