#include "time_diag.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "float_diag.h"
#include "float_utils.h"
#include "log.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "timer_utils.h"
#include "writer_config.h"

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif

#include "shared_array.h"

const char* TimeSrcToStr(const TimeSource_t time_source) {
    const char* name = "?";
    switch(time_source) {
    case TIME_SRC_SYSTICK:
        name = "SYSTICK";
        break;
    case TIME_SRC_RISC_V:
        name = "RISC_V";
        break;
    case TIME_SCR1_TIMER:
        name = "SCR1_TIMER";
        break;
    case TIME_SRC_ZEPHYR_CLOCK:
        name = "ZEPHYR_CLOCK";
        break;
    case TIME_SRC_WIN_CLOCK:
        name = "WIN_CLOCK";
        break;
    case TIME_SRC_SW_INCR:
        name = "SW_INCR";
        break;
    case TIME_SRC_RTC:
        name = "RTC";
        break;
    case TIME_SRC_TIMER5:
        name = "TIMER5";
        break;
    case TIME_SRC_TIMER4:
        name = "TIMER4";
        break;
    case TIME_SRC_TIMER3:
        name = "TIMER3";
        break;
    case TIME_SRC_TIMER2:
        name = "TIMER2";
        break;
    default: {
    } break;
    }
    return name;
}

const char* TimeMonth2Str(Month_t month) {
    const char* name = "?";
    switch((uint8_t)month) {
    case MON_JAN:
        name = "Jan";
        break;
    case MON_FEB:
        name = "Feb";
        break;
    case MON_MAR:
        name = "Mar";
        break;
    case MON_APR:
        name = "Apr";
        break;
    case MON_MAY:
        name = "May";
        break;
    case MON_JUN:
        name = "Jun";
        break;
    case MON_JUL:
        name = "Jul";
        break;
    case MON_AUG:
        name = "Aug";
        break;
    case MON_SEP:
        name = "Sep";
        break;
    case MON_OCT:
        name = "Oct";
        break;
    case MON_NOV:
        name = "Nov";
        break;
    case MON_DEC:
        name = "Dec";
        break;
    default: {
        snprintf(text, sizeof(text), "%u=?", month);
        name = text;

    } break;
    }
    return name;
}

bool Date2Str(const struct tm* const time_date, char* in_text, uint32_t size) {
    bool res = false;
    if(time_date) {
        if(in_text) {
            if(10 < size) {
                sprintf(in_text, "%d %s %d", time_date->tm_mday, TimeMonth2Str(time_date->tm_mon), time_date->tm_year);
                res = true;
            }
        }
    }
    return res;
}

bool TimeDate2Str(const struct tm* const time_date, char* in_text, uint32_t size) {
    bool res = false;
    if(time_date) {
        res = is_valid_time(time_date);
        if(res) {
            if(in_text) {
                if(20 < size) {
                    strcpy(in_text, "");
                    sprintf(in_text, "%s%02d:", text, time_date->tm_hour);
                    sprintf(in_text, "%s%02d:", text, time_date->tm_min);
                    sprintf(in_text, "%s%02d,", text, time_date->tm_sec);
                    sprintf(in_text, "%s%d,", text, time_date->tm_mday);
                    sprintf(in_text, "%s%s,", text, TimeMonth2Str(time_date->tm_mon));
                    sprintf(in_text, "%s%d,", text, time_date->tm_year);
                    res = true;
                } else {
                    LOG_ERROR(TIME, "OutMemTooLow,%u byte", size);
                }
            }
        } else {
            strcpy(in_text, "incorrect");
        }
    }
    return res;
}

bool Time2Str(const struct tm* const time_date, char* const in_text, uint32_t size) {
    bool res = false;
    if(time_date) {
        if(in_text) {
            if(10 < size) {
                sprintf(in_text, "%02d:%02d:%02d", time_date->tm_hour, time_date->tm_min, time_date->tm_sec);
                res = true;
            } else {
                LOG_ERROR(TIME, "OutMemTooLow %u byte", size);
            }
        }
    }
    return res;
}

const char* TimeDate2StrShort(const struct tm* const time_date) {
    strcpy(text, "");
    bool res = false;
    res = TimeDate2Str(time_date, text, sizeof(text));
    if(false == res) {
        strcpy(text, "Err");
    }
    return text;
}

const char* Time2StrShort(const struct tm* const time_date) {
    bool res = Time2Str(time_date, text, sizeof(text));
    if(false == res) {
        strcpy(text, "Err");
    }
    return text;
}

const char* Date2StrShort(const struct tm* const time_date) {
    bool res = Date2Str(time_date, text, sizeof(text));
    if(false == res) {
        strcpy(text, "Err");
    }
    return text;
}

bool TimeDate2CsvStr(const struct tm* const time_date, char* in_text, uint32_t size) {
    bool res = false;
    if(time_date) {
        if(in_text) {
            if(size) {
                time_t time_stamp = mktime((struct tm*)time_date);
                sprintf(in_text, "%02d:%02d:%02d, %d,%s,%d, %10d", time_date->tm_hour, time_date->tm_min,
                        time_date->tm_sec, time_date->tm_mday, TimeMonth2Str(time_date->tm_mon), time_date->tm_year,
                        (int32_t)time_stamp);
                res = true;
            }
        }
    }
    return res;
}

bool print_time_date(const char* const prefix, const struct tm* const time_date, bool is_one_line) {
    bool res = false;
    if(time_date) {
        if(false == is_one_line) {
            cli_printf("%7s" CRLF, prefix);
            cli_printf("time: %s" CRLF, Time2StrShort(time_date));
            cli_printf("date: %s" CRLF, Date2StrShort(time_date));
        } else {
            cli_printf("%7s %s %s" CRLF, prefix, Time2StrShort(time_date), Date2StrShort(time_date));
#if 0
            char text[80]="";
            res= TimeDate2Str( time_date, text, sizeof(text));
            if(res){
                cli_printf("%s %s" CRLF, prefix,text);
            }
#endif
        }
        res = true;
    }
    return res;
}

bool print_time(const struct tm* const time_date) {
    bool res = false;
    if(time_date) {
        LOG_INFO(TIME, "time: %d:%d:%d", time_date->tm_hour, time_date->tm_min, time_date->tm_sec);
        res = true;
    }
    return res;
}

bool UpTimeMs2Str(uint32_t up_time_ms, char* out_str, size_t size) {
    bool res = false;
    if(out_str) {
        strcpy(out_str, "");
        float up_time_min = MSEC_2_MIN(up_time_ms);
        if(up_time_min < 1.0) {
            snprintf(out_str, size, "%3u.%03u", (unsigned int)up_time_ms / 1000, (unsigned int)up_time_ms % 1000);
            res = true;
        } else {
            if((1.0 < up_time_min) && (up_time_min < 60.0)) {
                snprintf(out_str, size, "%u:%u", (unsigned int)up_time_min,
                         (unsigned int)((uint32_t)MSEC_2_SEC(up_time_ms)) % 60);
                res = true;
            } else if(24.0 < MIN_2_HOUR(up_time_min)) {
                float up_time_d = MIN_2_DAYS(up_time_min);
                // snprintf(out_str, size, "%7.3fd", up_time_d); /* inf in R32IMC */
                snprintf(out_str, size, "%sd", FloatToStr(up_time_d, 2));
                res = true;
            } else {
                float up_time_h = MSEC_2_HOUR(up_time_ms);
                snprintf(out_str, size, "%sh", FloatToStr(up_time_h, 2));
                res = true;
            }
        }
    }
    return res;
}

const char* UpTimeSec2Str(float up_time_s) {
    bool res = UpTimeMs2Str(up_time_s * 1000.0, text, sizeof(text));
    if(false == res) {
        LOG_ERROR(TIME, "UpTimeMs2StrErr %u", up_time_s);
    }
    return text;
}

const char* SecToStr(float sec) {
    if(sec < 60.0) {
        snprintf(text, sizeof(text), "%5.1f s", sec);
    } else if(sec < HOUR_2_SEC(1.0)) {
        snprintf(text, sizeof(text), "%5.1f m", SEC_2_MIN(sec));
    } else if(sec < DAY_2_SEC(1.0)) {
        snprintf(text, sizeof(text), "%5.1f h", SEC_2_HOUR(sec));
    } else if(sec < WEEK_2_SEC(1.0)) {
        snprintf(text, sizeof(text), "%5.1f d", SEC_2_DAYS(sec));
    } else {
        snprintf(text, sizeof(text), "%5.1f s", sec);
    }
    return text;
}

const char* UsecToStr(uint64_t uc_sec) {
#ifndef HAS_MIK32
    if(uc_sec < MSEC_2_USEC(1)) {
        snprintf(text, sizeof(text), "%llu us", uc_sec);
    } else if((MSEC_2_USEC(1) <= uc_sec) && (uc_sec < SEC_2_USEC(1))) {
        snprintf(text, sizeof(text), "%5.1f ms", USEC_2_MSEC(uc_sec));
    } else if(USEC_2_SEC(uc_sec) < 60.0) {
        snprintf(text, sizeof(text), "%5.1f s", USEC_2_SEC(uc_sec));
    } else {
        snprintf(text, sizeof(text), "%5.1f m", USEC_2_MIN(uc_sec));
    }
#endif
    return text;
}

const char* Ms2Str(uint32_t time_ms) {
    const char* name = UpTimeSec2Str(MSEC_2_SEC(time_ms));
    return name;
}

bool time_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {15, "Src"}, {9, "UpTimes"}, {8, "UpTimeMs"}, {7, "UpTimeUs"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    uint16_t time_cnt = time_get_cnt();
    for(i = 0; i <= time_cnt; i++) {
        TimeHandle_t* Node = TimeGetNode(i);
        if(Node) {
            float up_time_s = time_get_s(i);
            uint32_t up_time_ms = time_get_ms(i);
            uint64_t up_time_us = time_one_get_us(i);
            char logLine[150] = {0};
            strcpy(logLine, TSEP);
            snprintf(logLine, sizeof(logLine), "%s %3u " TSEP, logLine, i);
            snprintf(logLine, sizeof(logLine), "%s %13s " TSEP, logLine, TimeSrcToStr(Node->time_source));
            snprintf(logLine, sizeof(logLine), "%s %7s " TSEP, logLine, FloatToStr(up_time_s, 3));
            snprintf(logLine, sizeof(logLine), "%s %6u " TSEP, logLine, up_time_ms);
            snprintf(logLine, sizeof(logLine), "%s %" PRIu64 TSEP, logLine, up_time_us);

            cli_printf("%s" CRLF, logLine);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
