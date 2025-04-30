#include "log_diag.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "log.h"
#include "str_utils.h"
#ifdef HAS_SYSTEM_DIAG
#include "system_diag.h"
#endif
#include "table_utils.h"
#include "terminal_codes.h"
#include "writer_config.h"

const char* log_level_name_long(log_level_t level) {
    const char* result;
    switch(level) {
    case LOG_LEVEL_UNKNOWN:
        result = "?????";
        break;
    case LOG_LEVEL_PARANOID:
        result = "PARANOID";
        break;
    case LOG_LEVEL_DEBUG:
        result = "DEBUG";
        break;
    case LOG_LEVEL_NOTICE:
        result = "NOTICE";
        break;
    case LOG_LEVEL_INFO:
        result = "INFO";
        break;
    case LOG_LEVEL_WARNING:
        result = "WARNING";
        break;
    case LOG_LEVEL_ERROR:
        result = "ERROR";
        break;
    case LOG_LEVEL_CRITICAL:
        result = "CRITICAL";
        break;
    default:
        result = "?";
        break;
    }
    return result;
}

char log_level_name(log_level_t level) {
    char result = 'U';
    switch(level) {
    case LOG_LEVEL_INFO:
        result = 'I';
        break;
    case LOG_LEVEL_ERROR:
        result = 'E';
        break;
    case LOG_LEVEL_DEBUG:
        result = 'D';
        break;
    case LOG_LEVEL_UNKNOWN:
        result = 'U';
        break;
    case LOG_LEVEL_PARANOID:
        result = 'P';
        break;
    case LOG_LEVEL_NOTICE:
        result = 'N';
        break;
    case LOG_LEVEL_WARNING:
        result = 'W';
        break;
    case LOG_LEVEL_CRITICAL:
        result = 'C';
        break;
    case LOG_LEVEL_PROTECTED:
        result = 'T';
        break;
    default:
        result = '?';
        break;
    }
    return result;
}

log_level_t str2level(const char* str) {
    if(0 == strcasecmp(str, "P") || 0 == strcasecmp(str, "PARN") || 0 == strcasecmp(str, "PARANOID")) {
        return LOG_LEVEL_PARANOID;
    }
    if(0 == strcasecmp(str, "D") || 0 == strcasecmp(str, "DBG") || 0 == strcasecmp(str, "DEBUG")) {
        return LOG_LEVEL_DEBUG;
    }
    if(0 == strcasecmp(str, "n") || 0 == strcasecmp(str, "NOTI") || 0 == strcasecmp(str, "NOTICE")) {
        return LOG_LEVEL_NOTICE;
    }
    if(0 == strcasecmp(str, "I") || 0 == strcasecmp(str, "INF") || 0 == strcasecmp(str, "INFO")) {
        return LOG_LEVEL_INFO;
    }
    if(0 == strcasecmp(str, "W") || 0 == strcasecmp(str, "WARN") || 0 == strcasecmp(str, "WARNING")) {
        return LOG_LEVEL_WARNING;
    }
    if(0 == strcasecmp(str, "E") || 0 == strcasecmp(str, "ERR") || 0 == strcasecmp(str, "ERROR")) {
        return LOG_LEVEL_ERROR;
    }
    if(0 == strcasecmp(str, "C") || 0 == strcasecmp(str, "CRIT") || 0 == strcasecmp(str, "CRITICAL")) {
        return LOG_LEVEL_CRITICAL;
    }
    return LOG_LEVEL_UNKNOWN;
}

facility_t str2facility(const char* const str) {
    facility_t facility;
    facility_t result = UNKNOWN_FACILITY;
    for(facility = UNKNOWN_FACILITY; facility <= ALL_FACILITY; facility++) {
        const char* name = NULL;
#ifdef HAS_SYSTEM_DIAG
        name = Facility2Str(facility);
#endif
        if(0 == strcasecmp(name, str)) {
            result = facility;
            break;
        }
    }
    return result;
}

#ifdef HAS_LOG_COLOR
const char* log_level_color(log_level_t level) {
    const char* result = VT_SETCOLOR_NORMAL;
    switch(level) {
    case LOG_LEVEL_UNKNOWN:
        result = VT_SETCOLOR_NORMAL;
        break;
    case LOG_LEVEL_PARANOID:
        result = VT_SETCOLOR_PARANOID;
        break;
    case LOG_LEVEL_PROTECTED:
        result = VT_SETCOLOR_PINK;
        break;
    case LOG_LEVEL_DEBUG:
        result = VT_SETCOLOR_BLUE;
        break;
    case LOG_LEVEL_NOTICE:
        result = VT_SETCOLOR_NOTICE;
        break;
    case LOG_LEVEL_INFO:
        result = VT_SETCOLOR_GREEN;
        break;
    case LOG_LEVEL_WARNING:
        result = VT_SETCOLOR_YELLOW;
        break;
    case LOG_LEVEL_ERROR:
        result = VT_SETCOLOR_RED;
        break;
    case LOG_LEVEL_CRITICAL:
        result = VT_SETCOLOR_RED;
        break;

    default:
        result = "?";
        break;
    }
    return result;
}
#endif

bool log_level_diag(const char* const key_word1) {
    bool res = false;
    LOG_INFO(SYS, "KeyWord[%s]", key_word1);
    uint32_t num = 0;
    char log_line[150];
    // if(&(curWriterPtr->stream)) {
    facility_t facil = UNKNOWN_FACILITY;
    res = true;
    // uint16_t max_name_len=facility_max_name();
    static const table_col_t cols[] = {{4, "#"}, {4, "code"}, {16, "facility"}, {5, "lev"}, {10, "level"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(facil = UNKNOWN_FACILITY; facil < ALL_FACILITY; facil++) {
        const char* FacilityName = NULL;
#ifdef HAS_SYSTEM_DIAG
        FacilityName = Facility2Str(facil);
#endif
        if(FacilityName) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, facil);
            snprintf(log_line, sizeof(log_line), "%s %14s " TSEP, log_line, FacilityName);
            snprintf(log_line, sizeof(log_line), "%s %3d " TSEP, log_line, Log.levels[facil]);
#ifdef HAS_LOG_COLOR
            const char* color = log_level_color(Log.levels[facil]);
            snprintf(log_line, sizeof(log_line), "%s %s%8s%s " TSEP, log_line, color,
                     log_level_name_long(Log.levels[facil]), VT_SETCOLOR_NORMAL);
#endif
            const char* name = str_case_str(log_line, key_word1);
            if(name) {
                cli_printf(TSEP " %2u %s" CRLF, num + 1, log_line);
                num++;
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(0 < num) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
