#include "log.h"

#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#ifdef HAS_X86_64
#include <stdio.h>
#endif

#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

#ifdef HAS_LOG_UTILS
#include "log_utils.h"
#include "writer_config.h"
#include "writer_generic.h"
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
    .flush = false,
    .serial_nun = 0,
};

bool log_level_time_stamp(bool on_off) {
    bool res = false;
#ifdef HAS_LOG_TIME_STAMP
    Log.time_stamp = on_off;
    res = true;
#endif
    return res;
}

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
    res = writer_init();
#endif

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

static bool set_log_level_all(log_level_t level) {
    bool res = true;
    uint32_t f = 0;
    for(f = 0; f < sizeof(Log.levels) / sizeof(Log.levels[0]); f++) {
        Log.levels[f] = level;
    }
    return res;
}

bool set_log_level(facility_t facility, log_level_t level) {
    bool res = false;
    if(ALL_FACILITY == facility) {
        res = set_log_level_all(level);
    }
    if((UNKNOWN_FACILITY < facility) && (facility < ALL_FACILITY)) {
        Log.levels[facility] = level;
        res = true;
    }
    return res;
}

log_level_t log_level_get(facility_t facility) {
    log_level_t level = LOG_LEVEL_UNKNOWN;
    if((UNKNOWN_FACILITY < facility) && (facility < ALL_FACILITY)) {
        level = Log.levels[facility];
    }
    return level;
}

static bool is_log_enabled(log_level_t level, facility_t facility) {
    bool res = true;
    log_level_t log_level = log_level_get(facility);
    if(level < log_level) {
        res = false;
    }
    return res;
}

bool log_write_prefix(log_level_t level, facility_t facility) {
    bool res = false;
    res = is_log_enabled(level, facility);

    if(res) {
#ifdef HAS_LOG_TIME_STAMP
        uint32_t up_time_ms = 0;
        up_time_ms = time_get_ms32();
#endif /**/

#ifdef HAS_LOG_COLOR
        if(Log.colored) {
#ifdef HAS_LOG_DIAG
            const char* color = log_level_color(level);
            cli_putstr(color);
#endif /*HAS_LOG_DIAG*/
        }
#endif /*HAS_LOG_COLOR*/

#ifdef HAS_X86_64
        // cli_printf("\n");
#endif

#ifdef HAS_LOG_TIME_STAMP
        if(Log.time_stamp) {
            uint32_t up_time_s = up_time_ms / 1000;
            uint32_t up_time_ms_frac = up_time_ms % 1000;
            Log.serial_nun++;
            cli_printf("%u.%03u,%u ", up_time_s, up_time_ms_frac, Log.serial_nun);
        }
#endif /*HAS_LOG_TIME_STAMP*/

#ifdef HAS_LOG_DIAG
        if(Log.facility_name) {
            cli_printf("%c,", log_level_name(level));
#ifdef HAS_SYSTEM_DIAG
            cli_printf("[%s] ", Facility2Str(facility));
#endif /*HAS_SYSTEM_DIAG*/
        }
#endif /*HAS_LOG_DIAG*/
        res = true;
    }
    return res;
}

void log_write_end(void) {
#ifdef HAS_LOG_COLOR
    if(Log.colored) {
        cli_putstr(VT_SETCOLOR_NORMAL);
    }
#endif
    if(Log.new_line) {
#ifdef HAS_STREAM
        cli_putstr(CRLF);
#endif
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

void LOG_PARN(facility_t facility, const char* format, ...) {
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

void LOG_INFO(facility_t facility, const char* format, ...) {
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

void LOG_WARNING(facility_t facility, const char* format, ...) {
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

void LOG_ERROR(facility_t facility, const char* format, ...) {
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
    set_log_level(facility, log_level);
    return origin;
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

#ifdef HAS_PC
bool stdio_send(const uint8_t* const array, const uint32_t size) {
    bool res = false;
#ifdef HAS_ARRAY_DIAG
    cli_printf("%s", ArrayToStr(array, size));
    res = true;
#endif
    return res;
}
#endif

COMPONENT_INIT_PATTERT(LOG, LOG, log)
