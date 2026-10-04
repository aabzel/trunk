#include "log.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "compiler_const.h"

#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

#ifdef HAS_LOG_UTILS
#include "log_utils.h"
#include "writer.h"
#endif

#ifdef HAS_STREAM
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_STRING
#include "str_utils.h"
#endif

#ifdef HAS_SYSTEM_DIAG
#include "system_diag.h"
#endif

#ifdef HAS_LOG_COLOR
#include "terminal_codes.h"
#endif

#include "code_generator.h"

COMPONENT_GET_NODE(Log, log)
COMPONENT_GET_CONFIG(Log, log)

/*
 Current logging settings
 */
Log_t Log = {
#ifdef HAS_LOG_DIAG
    .facility_name = true,
#endif

#ifdef HAS_LOG_COLOR
    .colored = true,
#endif

#ifdef HAS_LOG_TIME_STAMP
    .time_stamp = true,
#endif
    .in_place = false,
    .flush = false,
    .serial_nun = 0,
};

bool log_level_in_place(bool on_off) {
    bool res = true;
    Log.in_place = on_off;
    return res;
}

log_level_t ResToLogLevel(const bool res) {
    log_level_t log_level = LOG_LEVEL_DEBUG;
    if(res) {
        log_level = LOG_LEVEL_NOTICE;
    } else {
        log_level = LOG_LEVEL_ERROR;
    }
    return log_level;
}

#ifdef HAS_LOG_TIME_STAMP
bool log_level_time_stamp(bool on_off) {
    bool res = false;
    Log.time_stamp = on_off;
    res = true;
    return res;
}
#endif

/*NOTE: log_init() is already busy name in Zephyr code base*/
bool log_initialize(void) {
    bool res = true;
    Log.new_line = true;
    Log.flush = false;
#ifdef HAS_LOG_DIAG
    Log.facility_name = true;
#endif

#ifdef HAS_LOG_COLOR
    Log.colored = true;
#endif

#ifdef HAS_LOG_TIME_STAMP
    Log.time_stamp = true;
#endif

#ifdef HAS_LOG_UTILS
    res = writer_mcal_init();
#endif

    uint32_t cnt = ARRAY_SIZE(Log.levels);
    uint32_t f = 0;
    for(f = 0; f < cnt; f++) {
        Log.levels[f].paranoid = 0;
        Log.levels[f].debug = 0;
        Log.levels[f].protected = 0;
        Log.levels[f].trace = 0;
        Log.levels[f].notice = 0;

        Log.levels[f].info = 1;
        Log.levels[f].warning = 1;
        Log.levels[f].error = 1;
        Log.levels[f].critical = 1;
    }

    return res;
}

#ifdef HAS_LOG_UTILS
bool log_print_conditional(log_level_t level, facility_t facility, const char* const in_text,
                           const char* const key_word1, const char* const key_word2) {
    bool res = false;
    LOG_PARN(facility, "%s", text);
    if(in_text && key_word1 && key_word2) {
        res = true;
#ifdef HAS_STRING
        res = is_contain(in_text, key_word1, key_word2);
#endif /*HAS_STRING*/
        if(res) {
            log_write(level, facility, "%s", in_text);
            res = true;
        }
    } else if(in_text && key_word1 && NULL == key_word2) {
        res = true;
#ifdef HAS_STRING
        res = is_contain(in_text, key_word1, "");
#endif /*HAS_STRING*/
        if(res) {
            log_write(level, facility, "%s", in_text);
            res = true;
        }
    } else if(in_text && NULL == key_word1 && key_word2) {
        res = true;
#ifdef HAS_STRING
        res = is_contain(in_text, key_word2, "");
#endif /*HAS_STRING*/
        if(res) {
            log_write(level, facility, "%s", in_text);
            res = true;
        }
    } else {
        LOG_ERROR(facility, "KeyWordsError");
        res = false;
    }
    return res;
}
#endif /*HAS_LOG_UTILS*/

static bool log_level_set_all(log_level_t level) {
    bool res = true;
    uint32_t f = 0;
    for(f = 0; f < sizeof(Log.levels) / sizeof(Log.levels[0]); f++) {
        // Log.levels[f] = level;
        switch(level) {
        case LOG_LEVEL_PARANOID: {
            Log.levels[f].paranoid = 1;
            res = true;
        } break;
        case LOG_LEVEL_DEBUG: {
            Log.levels[f].debug = 1;
            res = true;
        } break;
        case LOG_LEVEL_PROTECTED: {
            Log.levels[f].protected = 1;
            res = true;
        } break;
        case LOG_LEVEL_NOTICE: {
            Log.levels[f].notice = 1;
            res = true;
        } break;
        case LOG_LEVEL_INFO: {
            Log.levels[f].info = 1;
            res = true;
        } break;
        case LOG_LEVEL_WARNING: {
            Log.levels[f].warning = 1;
            res = true;
        } break;
        case LOG_LEVEL_ERROR: {
            Log.levels[f].error = 1;
            res = true;
        } break;
        case LOG_LEVEL_TRACE: {
            Log.levels[f].trace = 1;
            res = true;
        } break;
        case LOG_LEVEL_CRITICAL: {
            Log.levels[f].critical = 1;
            res = true;
        } break;
        case LOG_LEVEL_DISABLE: {
            Log.levels[f].word = 0;
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }
    }
    return res;
}

static bool log_level_reset_all(const log_level_t level) {
    bool res = true;
    uint32_t f = 0;
    for(f = 0; f < ARRAY_SIZE(Log.levels); f++) {
        switch(level) {
        case LOG_LEVEL_PARANOID: {
            Log.levels[f].paranoid = 0;
            res = true;
        } break;
        case LOG_LEVEL_DEBUG: {
            Log.levels[f].debug = 0;
            res = true;
        } break;
        case LOG_LEVEL_PROTECTED: {
            Log.levels[f].protected = 0;
            res = true;
        } break;
        case LOG_LEVEL_NOTICE: {
            Log.levels[f].notice = 0;
            res = true;
        } break;
        case LOG_LEVEL_INFO: {
            Log.levels[f].info = 0;
            res = true;
        } break;
        case LOG_LEVEL_WARNING: {
            Log.levels[f].warning = 0;
            res = true;
        } break;
        case LOG_LEVEL_ERROR: {
            Log.levels[f].error = 0;
            res = true;
        } break;
        case LOG_LEVEL_TRACE: {
            Log.levels[f].trace = 0;
            res = true;
        } break;
        case LOG_LEVEL_CRITICAL: {
            Log.levels[f].critical = 0;
            res = true;
        } break;
        case LOG_LEVEL_DISABLE: {
            Log.levels[f].word = 0;
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }
    }
    return res;
}

bool set_log_level(facility_t facility, log_level_t level) {
    bool res = false;
    if(ALL_FACILITY == facility) {
        res = log_level_set_all(level);
    }
    if((UNKNOWN_FACILITY < facility) && (facility < ALL_FACILITY)) {
        // Log.levels[facility] = level;

        switch(level) {
        case LOG_LEVEL_PARANOID: {
            Log.levels[facility].paranoid = 1;
            res = true;
        } break;
        case LOG_LEVEL_DEBUG: {
            Log.levels[facility].debug = 1;
            res = true;
        } break;
        case LOG_LEVEL_PROTECTED: {
            Log.levels[facility].protected = 1;
            res = true;
        } break;
        case LOG_LEVEL_NOTICE: {
            Log.levels[facility].notice = 1;
            res = true;
        } break;
        case LOG_LEVEL_INFO: {
            Log.levels[facility].info = 1;
            res = true;
        } break;
        case LOG_LEVEL_WARNING: {
            Log.levels[facility].warning = 1;
            res = true;
        } break;
        case LOG_LEVEL_ERROR: {
            Log.levels[facility].error = 1;
            res = true;
        } break;
        case LOG_LEVEL_TRACE: {
            Log.levels[facility].trace = 1;
            res = true;
        } break;
        case LOG_LEVEL_CRITICAL: {
            Log.levels[facility].critical = 1;
            res = true;
        } break;
        case LOG_LEVEL_DISABLE: {
            Log.levels[facility].word = 0;
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }
        res = true;
    }
    return res;
}

bool log_level_set(facility_t facility, log_level_t level) {
    bool res = false;
    res = set_log_level(facility, level);
    return res;
}

bool log_level_reset(const facility_t facility, const log_level_t level) {
    bool res = false;
    if(ALL_FACILITY == facility) {
        res = log_level_reset_all(level);
    }

    if(UNKNOWN_FACILITY < facility) {
        if(facility < ALL_FACILITY) {
            switch(level) {
            case LOG_LEVEL_PARANOID: {
                Log.levels[facility].paranoid = 0;
                res = true;
            } break;
            case LOG_LEVEL_DEBUG: {
                Log.levels[facility].debug = 0;
                res = true;
            } break;
            case LOG_LEVEL_PROTECTED: {
                Log.levels[facility].protected = 0;
                res = true;
            } break;
            case LOG_LEVEL_NOTICE: {
                Log.levels[facility].notice = 0;
                res = true;
            } break;
            case LOG_LEVEL_INFO: {
                Log.levels[facility].info = 0;
                res = true;
            } break;
            case LOG_LEVEL_WARNING: {
                Log.levels[facility].warning = 0;
                res = true;
            } break;
            case LOG_LEVEL_ERROR: {
                Log.levels[facility].error = 0;
                res = true;
            } break;
            case LOG_LEVEL_TRACE: {
                Log.levels[facility].trace = 0;
                res = true;
            } break;
            case LOG_LEVEL_CRITICAL: {
                Log.levels[facility].critical = 0;
                res = true;
            } break;
            case LOG_LEVEL_DISABLE: {
                Log.levels[facility].word = 0;
                res = true;
            } break;
            default: {
                res = false;
            } break;
            }
        }
    }
    return res;
}

log_level_t log_level_min_get(const LogLevels_t LogLevelTotal) {
    log_level_t level = LOG_LEVEL_UNKNOWN;

    if(0 == LogLevelTotal.word) {
        level = LOG_LEVEL_DISABLE;
    }

    if(LogLevelTotal.critical) {
        level = LOG_LEVEL_CRITICAL;
    }

    if(LogLevelTotal.trace) {
        level = LOG_LEVEL_TRACE;
    }

    if(LogLevelTotal.error) {
        level = LOG_LEVEL_ERROR;
    }

    if(LogLevelTotal.warning) {
        level = LOG_LEVEL_WARNING;
    }

    if(LogLevelTotal.info) {
        level = LOG_LEVEL_INFO;
    }

    if(LogLevelTotal.notice) {
        level = LOG_LEVEL_NOTICE;
    }

    if(LogLevelTotal.protected) {
        level = LOG_LEVEL_PROTECTED;
    }

    if(LogLevelTotal.debug) {
        level = LOG_LEVEL_DEBUG;
    }
    if(LogLevelTotal.paranoid) {
        level = LOG_LEVEL_PARANOID;
    }

    return level;
}

log_level_t log_level_get(facility_t facility) {
    log_level_t level = LOG_LEVEL_UNKNOWN;
    if((UNKNOWN_FACILITY < facility) && (facility < ALL_FACILITY)) {
        if(0 == Log.levels[facility].word) {
            level = LOG_LEVEL_DISABLE;
        }

        if(Log.levels[facility].critical) {
            level = LOG_LEVEL_CRITICAL;
        }

        if(Log.levels[facility].trace) {
            level = LOG_LEVEL_TRACE;
        }

        if(Log.levels[facility].error) {
            level = LOG_LEVEL_ERROR;
        }

        if(Log.levels[facility].warning) {
            level = LOG_LEVEL_WARNING;
        }

        if(Log.levels[facility].info) {
            level = LOG_LEVEL_INFO;
        }

        if(Log.levels[facility].notice) {
            level = LOG_LEVEL_NOTICE;
        }

        if(Log.levels[facility].protected) {
            level = LOG_LEVEL_PROTECTED;
        }

        if(Log.levels[facility].debug) {
            level = LOG_LEVEL_DEBUG;
        }
        if(Log.levels[facility].paranoid) {
            level = LOG_LEVEL_PARANOID;
        }
    }
    return level;
}

LogLevels_t log_level_combined_get(const facility_t facility) {
    LogLevels_t LogLevels = {0};
    bool res = system_is_vaild_facility(facility);
    if(res) {
        LogLevels = Log.levels[facility];
    }
    return LogLevels;
}

static bool is_log_enabled(log_level_t level, facility_t facility) {
    bool res = false;
    LogLevels_t logLevel = log_level_combined_get(facility);

    switch(level) {
    case LOG_LEVEL_PARANOID: {
        res = logLevel.paranoid;
    } break;
    case LOG_LEVEL_DEBUG: {
        res = logLevel.debug;
    } break;
    case LOG_LEVEL_PROTECTED: {
        res = logLevel.protected;
    } break;
    case LOG_LEVEL_INFO: {
        res = logLevel.info;
    } break;
    case LOG_LEVEL_NOTICE: {
        res = logLevel.notice;
    } break;
    case LOG_LEVEL_WARNING: {
        res = logLevel.warning;
    } break;
    case LOG_LEVEL_ERROR: {
        res = logLevel.error;
    } break;
    case LOG_LEVEL_TRACE: {
        res = logLevel.trace;
    } break;
    case LOG_LEVEL_CRITICAL: {
        res = logLevel.critical;
    } break;
    default:
        break;
    }
    return res;
}

bool log_write_prefix(log_level_t level, facility_t facility) {
    bool res = false;
    char temp[40] = {0};
    memset(temp, 0, sizeof(temp));

    res = is_log_enabled(level, facility);

    if(res) {
        if(Log.in_place) {
            strcpy(temp, "\r");
        }

        if(Log.new_line) {
#ifdef HAS_STREAM
            // cli_putstr(CRLF);
#endif
        }

#ifdef HAS_LOG_TIME_STAMP
        uint32_t up_time_ms = time_get_ms32();
        (void)up_time_ms;
#endif /**/

#ifdef HAS_LOG_COLOR
        if(Log.colored) {
#ifdef HAS_LOG_DIAG
            const char* color = log_level_color(level);
            // cli_putstr(color);
            snprintf(temp, sizeof(temp), "%s%s", temp, color);
#endif /*HAS_LOG_DIAG*/
        }
#endif /*HAS_LOG_COLOR*/

#ifdef HAS_LOG_TIME_STAMP
        if(Log.time_stamp) {
            uint32_t up_time_s = up_time_ms / 1000;
            uint32_t up_time_ms_frac = up_time_ms % 1000;
            snprintf(temp, sizeof(temp), "%s%u.", temp, up_time_s);
            snprintf(temp, sizeof(temp), "%s%03u,", temp, up_time_ms_frac);
#ifdef HAS_LOG_TIME_STAMP_DIFF
            uint32_t time_diff_ms = up_time_ms - Log.up_time_prev_ms;
            snprintf(temp, sizeof(temp), "%s+%u,", temp, time_diff_ms);
#endif

            Log.up_time_prev_ms = up_time_ms;
        }
#endif /*HAS_LOG_TIME_STAMP*/

        Log.serial_nun++;
        snprintf(temp, sizeof(temp), "%s%u,", temp, Log.serial_nun);
#ifdef HAS_LOG_DIAG
        if(Log.facility_name) {
            snprintf(temp, sizeof(temp), "%s%c,", temp, log_level_name(level));

#ifdef HAS_SYSTEM_DIAG
            // cli_printf("[%s] ", FacilityToStr(facility));
            snprintf(temp, sizeof(temp), "%s[%s],", temp, FacilityToStr(facility));
#endif /*HAS_SYSTEM_DIAG*/
        }
#endif /*HAS_LOG_DIAG*/
        res = true;
    }
    cli_printf("%s", temp);

    return res;
}

void log_write_end(void) {
#ifdef HAS_LOG_COLOR
    if(Log.colored) {
        cli_putstr(VT_SETCOLOR_NORMAL);
    }
#endif

    if(Log.new_line) {
        if(!Log.in_place) {
#ifdef HAS_STREAM
            cli_putstr(CRLF);
#endif
        }
    }

#ifndef NO_EMBEDED
    if(Log.flush) {
#ifdef HAS_PRINTF
        flush_printf();
#endif
    }
#endif
}

void log_write(log_level_t level, facility_t facility, const char* format, ...) {
#ifdef HAS_STREAM
    bool res = log_write_prefix(level, facility);
    if(res) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_WARNING(facility_t facility, const char* format, ...) {
//    log_write(LOG_LEVEL_WARNING, facility, format); does not work
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_WARNING, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_INFO(facility_t facility, const char* format, ...) {
    // log_write(LOG_LEVEL_INFO, facility, format); does not work
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_INFO, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_PARN(facility_t facility, const char* format, ...) {
    // log_write(LOG_LEVEL_PARANOID, facility, format); does not work
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_PARANOID, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_DEBUG(facility_t facility, const char* format, ...) {
    /* log_write(LOG_LEVEL_DEBUG, facility, format); does not work*/
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_DEBUG, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_NOTICE(facility_t facility, const char* format, ...) {
    /* log_write(LOG_LEVEL_NOTICE, facility, format); does not work */
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_NOTICE, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_PROTECTED(facility_t facility, const char* format, ...) {
    /* log_write(LOG_LEVEL_PROTECTED, facility, format); does not work */
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_PROTECTED, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_ERROR(facility_t facility, const char* format, ...) {
    /* log_write(LOG_LEVEL_ERROR, facility, format); does not work */
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_ERROR, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_CRITICAL(facility_t facility, const char* format, ...) {
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_CRITICAL, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

void LOG_TRACE(facility_t facility, const char* format, ...) {
#ifdef HAS_STREAM
    if(log_write_prefix(LOG_LEVEL_TRACE, facility)) {
        va_list va;
        va_start(va, format);
        cli_vprintf(format, va);
        va_end(va);
        log_write_end();
    }
#endif
}

log_level_t ErrValue2LogLevel(int32_t val) {
    log_level_t out_log_level = LOG_LEVEL_INFO;
    if(0 == val) {
        out_log_level = LOG_LEVEL_INFO;
    } else if(1 == val) {
        out_log_level = LOG_LEVEL_WARNING;
    } else {
        out_log_level = LOG_LEVEL_ERROR;
    }
    return out_log_level;
}

log_level_t log_level_get_set(facility_t facility, log_level_t log_level) {
    log_level_t origin = log_level_get(facility);
    log_level_set(facility, log_level);
    return origin;
}

bool log_res_u32(const facility_t facility, const bool res, const char* const in_text, const uint32_t value) {
#ifdef HAS_STREAM
    if(res) {
        LOG_DEBUG(facility, "%s:%u,Ok", in_text, value);
    } else {
        LOG_ERROR(facility, "%s:%u,Err", in_text, value);
    }
#endif
    return res;
}

bool log_res(const facility_t facility, const bool res, const char* const in_text) {
#ifdef HAS_STREAM
    if(res) {
        LOG_DEBUG(facility, "%s,Ok", in_text);
    } else {
        LOG_ERROR(facility, "%s,Err", in_text);
    }
#endif
    return res;
}

bool log_parn_res(const facility_t facility, const bool res, const char* const in_text) {
#ifdef HAS_STREAM
    if(res) {
        LOG_PARN(facility, "%s,Ok", in_text);
    } else {
        LOG_ERROR(facility, "%s,Err", in_text);
    }
#endif
    return res;
}

bool log_debug_res(const facility_t facility, const bool res, const char* const in_text) {
#ifdef HAS_STREAM
    if(res) {
        LOG_DEBUG(facility, "%s,Ok", in_text);
    } else {
        LOG_ERROR(facility, "%s,Err", in_text);
    }
#endif
    return res;
}

bool log_info_res(const facility_t facility, const bool res, const char* const in_text) {
#ifdef HAS_STREAM
    if(res) {
        LOG_INFO(facility, "%s,Ok", in_text);
    } else {
        LOG_ERROR(facility, "%s,Err", in_text);
    }
#endif
    return res;
}

bool log_info_res_u32(const facility_t facility, const bool res, const char* const in_text, const uint32_t value) {
#ifdef HAS_STREAM
    if(res) {
        LOG_INFO(facility, "%s:%u,Ok", in_text, value);
    } else {
        LOG_ERROR(facility, "%s:%u,Err", in_text, value);
    }
#endif
    return res;
}

_WEAK_FUN_
void cli_printf(const char* format, ...) {}

_WEAK_FUN_
void cli_putstr(const char* str) {}

_WEAK_FUN_
void cli_putchar(char ch) {}

_WEAK_FUN_
void cli_vprintf(const char* format, va_list vlist) {}

bool log_mcal_init_disable(void) {
    bool res = true;
    uint32_t f = UNKNOWN_FACILITY;
    for(f = 0; f <= ALL_FACILITY; f++) {
        res = log_level_set((facility_t)f, LOG_LEVEL_DISABLE);
    }
    res = log_level_set(SYS, LOG_LEVEL_DISABLE);
    return res;
}

bool log_enable(void) {
    bool res = true;
    uint32_t f = UNKNOWN_FACILITY;
    for(f = 0; f <= ALL_FACILITY; f++) {
        res = log_level_set((facility_t)f, LOG_LEVEL_INFO);
    }
    return res;
}

static bool log_init_custom(void) {
    bool res = true;
    res = log_initialize();
    return res;
}

static bool log_init_one(uint8_t num) {
    bool res = false;
    const LogConfig_t* Config = LogGetConfig(num);
    if(Config) {
        LogHandle_t* Node = LogGetNode(num);
        if(Node) {
            Node->colored = Config->colored;
            Node->time_stamp = Config->time_stamp;
            res = true;
        } else {
#ifdef HAS_MIK32
            res = log_fix();
#endif
        }
    } else {
#ifdef HAS_MIK32
        res = log_fix();
#endif
    }
    return res;
}

COMPONENT_INIT_PATTERT(LOG, LOG, log)
