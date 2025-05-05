#include "date_mcal.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code_generator.h"
#include "std_includes.h"

#ifdef HAS_RISC_V
#include "rv32imc_driver.h"
#endif

#ifdef HAS_SCR1_TIMER
#include "scr1_timer/scr1_timer.h"
#endif

COMPONENT_GET_NODE(Time, time)

COMPONENT_GET_CONFIG(Time, time)

#ifdef HAS_PC
#include "cli_wrappers.h"
#include "scan_serial_port.h"
#include <time.h>
#endif /*HAS_PC*/

#ifdef HAS_ZEPHYR
#include <zephyr/kernel.h>
#endif /*HAS_ZEPHYR*/

#ifdef HAS_SYSTICK
//#include "systick.h"
#include "systick_mcal.h"
#endif

#ifdef HAS_TIME_DIAG
#include "time_diag.h"
#endif

#ifdef HAS_X86_64
#include <sys/timeb.h>
#endif /**/

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif /**/

#ifdef HAS_DS3231
#include "ds3231_drv.h"
#endif /**/

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_RTC
#include "rtc_mcal.h"
#endif /*HAS_RTC*/

#ifdef HAS_GNSS
#include "gnss_drv.h"
#endif /**/

#ifdef HAS_LOG
#include "log.h"
#endif /**/

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif /**/

#ifdef HAS_TIMER
#include "timer_mcal.h"
#include "timer_utils.h"
#endif /*HAS_TIMER*/

#ifdef HAS_STRING
#include "convert.h"
#endif /**/

#include "data_utils.h"

#ifdef ESP32
uint32_t g_up_time_ms;
#endif

#ifdef HAS_X86
uint32_t start_time_ms;
uint32_t g_up_time_ms;
time_t start_time = 0;
struct timeb start_time_b;
#endif

#ifdef HAS_TIME_EXT
uint32_t calc_days_in_year(const struct tm* const date) {
    /*TODO*/
    return 365;
}
#endif

#ifdef HAS_TIME_EXT
// UTC hour in hhmmss format
bool parse_time_from_val(uint32_t packed_time, struct tm* tm_stamp) {
    bool res = false;
    if(tm_stamp) {
        res = true;
        tm_stamp->tm_sec = extract_digit(packed_time, 1) * 10 + extract_digit(packed_time, 0);
        if(60 <= tm_stamp->tm_sec) {
            res = false;
        }
        if(true == res) {
            tm_stamp->tm_min = extract_digit(packed_time, 3) * 10 + extract_digit(packed_time, 2);
            if(60 <= tm_stamp->tm_min) {
                res = false;
            }
        }

        if(true == res) {
            tm_stamp->tm_hour = extract_digit(packed_time, 5) * 10 + extract_digit(packed_time, 4);
            if(24 <= tm_stamp->tm_hour) {
                res = false;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_TIME_EXT
bool time_get_cur(struct tm* timeinfo) {
    bool res = false;
#ifdef HAS_DS3231
    res = ds3231_get_time_date(1, timeinfo);
#endif

#ifdef HAS_PC
    time_t seconds;
    seconds = time(NULL);
    struct tm* cur_time;
    cur_time = localtime(&seconds);
    memcpy(timeinfo, cur_time, sizeof(struct tm));
    timeinfo->tm_year += 1900;

    // time_t now = time(0);
    // timeinfo = ctime(&now);
    res = true;
#endif
    return res;
}
#endif

#ifdef HAS_TIME_EXT
struct tm* time_get_time(void) {
    bool res = false;
    (void)res;
    struct tm* time = NULL;

#if defined(HAS_DATE) && defined(HAS_GNSS)
    GnssHandle_t* GnssNode = GnssGetNode(1);
    if(GnssNode) {
        res = is_valid_time_date(&GnssNode->time_date);
        if(res) {
            time = &GnssNode->time_date;
        }
    }
#endif
    if(false == res) {
#ifdef HAS_SW_RTC
        res = calendar_gettime(&SwRtc.date_time);
        if(res) {
            time = &SwRtc.date_time;
        }
#endif
    }
    return time;
}
#endif

#ifdef HAS_DATE

/* date in ddmmaa format */
bool parse_date_from_val(uint32_t packed_date, struct tm* tm_stamp) {
    bool res = false;
    if(tm_stamp) {
        res = true;
        tm_stamp->tm_mday = extract_digit(packed_date, 5) * 10 + extract_digit(packed_date, 4);
        if(32 <= tm_stamp->tm_mday) {
            res = false;
        }
        if(true == res) {
            tm_stamp->tm_mon =
                extract_digit(packed_date, 3) * 10 + extract_digit(packed_date, 2) - 1; /*Ublox count from 1*/
            if(13 <= tm_stamp->tm_mon) {
                res = false;
            }
        }

        if(true == res) {
            tm_stamp->tm_year = extract_digit(packed_date, 1) * 10 + extract_digit(packed_date, 0);
            tm_stamp->tm_year += 2000;
        }
    }
    return res;
}

#endif

#ifdef HAS_DATE
bool is_time_date_equal_soft(const struct tm* const date_time1, const struct tm* const date_time2, uint32_t sec_error,
                             int32_t* real_error) {
    bool res = false;

    int32_t diff = time_date_cmp(date_time1, date_time2);
    if(abs(diff) < sec_error) {
        res = true;
    } else {
        res = false;
    }
    if(real_error) {
        *real_error = diff;
    }
    return res;
}
#endif

#ifdef HAS_DATE
bool is_time_date_equal(struct tm* date_time1, struct tm* date_time2) {
    bool res = true;
    if(res) {
        if(date_time1->tm_year == date_time2->tm_year) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_DEBUG(TIME, "WrongYear %u %u", date_time1->tm_year, date_time2->tm_year);
#endif
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_mon == date_time2->tm_mon) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_DEBUG(TIME, "WrongMon %u %u", date_time1->tm_mon, date_time2->tm_mon);
#endif
            res = false;
        }
    }
    if(res) {
        if(date_time1->tm_mday == date_time2->tm_mday) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongDay %u %u", date_time1->tm_mday, date_time2->tm_mday);
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_hour == date_time2->tm_hour) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongHour %u %u", date_time1->tm_hour, date_time2->tm_hour);
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_min == date_time2->tm_min) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongMin %u %u", date_time1->tm_min, date_time2->tm_min);
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_sec == date_time2->tm_sec) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongSec %u %u", date_time1->tm_sec, date_time2->tm_sec);
            res = false;
        }
    }

    return res;
}
#endif

#ifdef HAS_DATE
bool is_valid_date(const struct tm* const date_time) {
    bool res = true;
    if(res) {
        /*TODO Rewise*/
        if((0 <= date_time->tm_year) && (date_time->tm_year < 2150)) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongYear %u", date_time->tm_year);
            res = false;
        }
    }
    if(res) {
        if((0 <= date_time->tm_mon) && (date_time->tm_mon <= 11)) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongMon %u", date_time->tm_mon);
            res = false;
        }
    }
    if(res) {
        if((1 <= date_time->tm_mday) && (date_time->tm_mday <= 31)) {
            res = true;
        } else {
            LOG_DEBUG(TIME, "WrongDay %u", date_time->tm_mday);
            res = false;
        }
    }

    return res;
}
#endif

#ifdef HAS_TIME_EXT
bool is_valid_time(const struct tm* const date_time) {
    bool res = true;
    if(res) {
        if((0 <= date_time->tm_hour) && (date_time->tm_hour <= 23)) {
            res = true;
        } else {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIME, "WrongHour %u", date_time->tm_hour);
#endif
        }
    }

    if(res) {
        if((0 <= date_time->tm_min) && (date_time->tm_min <= 59)) {
            res = true;
        } else {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIME, "WrongMin %u", date_time->tm_min);
#endif
        }
    }

    if(res) {
        if((0 <= date_time->tm_sec) && (date_time->tm_sec <= 59)) {
            res = true;
        } else {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIME, "WrongSec %u", date_time->tm_sec);
#endif
        }
    }

    return res;
}
#endif

#ifdef HAS_DATE
bool is_valid_time_date(const struct tm* const date_time) {
    bool res = true;

    res = is_valid_date(date_time);

    if(res) {
        res = is_valid_time(date_time);
    }

    return res;
}
#endif

#ifdef HAS_TIME_EXT
bool time_get_time_str(char* const out_str, uint32_t size) {
    bool res = false;
    if(out_str && (0 < size)) {
        strncpy(out_str, "", size);
#ifdef HAS_CALENDAR
        struct tm* curTime = time_get_time();
        if(curTime) {
            res = is_valid_time(curTime);
            if(res) {
                snprintf(out_str, size, "%02u:%02u:%02u", curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
            }
        }

#else /*HAS_CALENDAR*/

#ifdef HAS_TIME
#ifdef HAS_TIME_DIAG
        uint32_t up_time_ms = time_get_ms32();
        UpTimeMs2Str(up_time_ms, out_str, size);
#endif /*HAS_TIME_DIAG*/
#endif /*HAS_CLOCK*/
#endif /*HAS_CALENDAR*/
        res = true;
    }
    return res;
}
#endif /*HAS_CALENDAR*/

#ifdef HAS_DATE
/*000000000011111111112222*/
/*012345678901234567890123*/
/*Tue Dec  7 15:34:46 2021*/
bool time_data_parse(struct tm* date_time, char* str) {
    bool res = false;
    if(date_time && str) {
#ifdef HAS_RTC
        LOG_INFO(LG_RTC, "init time by [%s]", str);
#endif
        uint32_t cnt = 0;
        res = try_strl2int32(&str[17], 2, (int32_t*)&date_time->tm_sec);
        if(res) {
            cnt++;
        } else {
#ifdef HAS_X86_64
            LOG_ERROR(TIME, " ErrParse sec [%s]", &str[17]);
#endif
        }

        res = try_strl2int32(&str[14], 2, (int32_t*)&date_time->tm_min);
        if(res) {
            cnt++;
        } else {
#ifdef HAS_X86_64
            LOG_ERROR(TIME, " ErrParse min [%s]", &str[14]);
#endif
        }

        res = try_strl2int32(&str[11], 2, (int32_t*)&date_time->tm_hour);
        if(res) {
            cnt++;
        } else {
#ifdef HAS_X86_64
            LOG_ERROR(TIME, " ErrParse hour [%s]", &str[11]);
#endif
        }

        res = try_strl2month(&str[4], (int32_t*)&date_time->tm_mon);
        if(res) {
            cnt++;
        } else {
#ifdef HAS_X86_64
            LOG_ERROR(TIME, " ErrParse mon [%s]", &str[4]);
#endif
        }

        res = try_strl2int32(&str[8], 2, (int32_t*)&date_time->tm_mday);
        if(res) {
            cnt++;
        } else {
#ifdef HAS_X86_64
            LOG_ERROR(TIME, " ErrParse mday [%s]", &str[8]);
#endif
        }
        res = try_strl2int32(&str[20], 4, (int32_t*)&date_time->tm_year);
        if(res) {
            cnt++;
        } else {
#ifdef HAS_X86_64
            LOG_ERROR(TIME, " ErrParse year [%s]", &str[20]);
#endif
        }

        if(6 == cnt) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}
#endif

#ifdef HAS_STRING
/*13:32:47*/
bool time_parse(struct tm* const date_time, char* str) {
    bool res = false;
    if(date_time && str) {
        LOG_INFO(TIME, "init time by [%s]", str);
        uint32_t cnt = 0;
        res = try_strl2int32(&str[6], 2, (int32_t*)&date_time->tm_sec);
        if(res) {
            LOG_INFO(TIME, "Sec %d", date_time->tm_sec);
            cnt++;
        } else {
            LOG_ERROR(TIME, "ErrParse sec [%s]", &str[6]);
        }

        res = try_strl2int32(&str[3], 2, (int32_t*)&date_time->tm_min);
        if(res) {
            LOG_INFO(TIME, "Min %d", date_time->tm_min);
            cnt++;
        } else {
            LOG_ERROR(TIME, "[e] ErrParse min [%s]", &str[3]);
        }

        res = try_strl2int32(&str[0], 2, (int32_t*)&date_time->tm_hour);
        if(res) {
            LOG_INFO(TIME, "Hour %d", date_time->tm_hour);
            cnt++;
        } else {
            LOG_ERROR(TIME, "ErrParse hour [%s]", &str[0]);
        }

        if(3 == cnt) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}
#endif

#ifdef HAS_DATE
// Dec 21 2021
// Jan 10 2022
bool date_parse(struct tm* date_time, char* str) {
    bool res = false;
    if(date_time && str) {
#ifdef HAS_RTC
        LOG_INFO(LG_RTC, "init time by [%s]", str);
#endif
        uint32_t cnt = 0;

        res = try_strl2month(&str[0], (int32_t*)&date_time->tm_mon);
        if(res) {
            cnt++;
            LOG_DEBUG(TIME, "Parse mon %d", date_time->tm_mon);
        } else {
            LOG_ERROR(TIME, "ErrParse mon [%s]", &str[0]);
        }

        res = try_strl2int32(&str[4], 2, (int32_t*)&date_time->tm_mday);
        if(res) {
            cnt++;
            LOG_DEBUG(TIME, "Parse mday %u", date_time->tm_mday);
        } else {
            LOG_ERROR(TIME, "ErrParse mday [%s]", &str[4]);
        }
        res = try_strl2int32(&str[7], 4, (int32_t*)&date_time->tm_year);
        if(res) {
            LOG_DEBUG(TIME, "Parse year %d", date_time->tm_year);
            cnt++;
        } else {
            LOG_ERROR(TIME, "ErrParse year [%s]", &str[7]);
        }

        if(3 == cnt) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}
#endif

#ifdef HAS_PC

static uint32_t pc_clock_get_ms(void) {
    uint32_t time_ms = 0;
    clock_t cur_clock = 0;
    cur_clock = clock();
    time_ms = (uint32_t)((1000 * cur_clock) / CLOCKS_PER_SEC);

    return time_ms;
}

static uint64_t pc_clock_get_us(void) {
    uint64_t time_us = 0;
    clock_t cur_clock = clock();
    time_us = (uint64_t)((1000000U * ((uint64_t)cur_clock)) / ((uint64_t)CLOCKS_PER_SEC));
    return time_us;
}
#endif /*HAS_PC*/

#ifdef HAS_DATE
int32_t time_date_cmp(const struct tm* const date_time1, const struct tm* const date_time2) {
    int32_t diff_sec = INT_MAX;
    log_level_t ll = log_level_get(TIME);

    if(LOG_LEVEL_DEBUG == ll) {
        print_time_date("Time1", date_time1, true);
        print_time_date("Time2", date_time2, true);
    }

    time_t time_stamp1 = mktime((struct tm*)date_time1);
    time_t time_stamp2 = mktime((struct tm*)date_time2);
    if((0 < time_stamp1) && (0 < time_stamp2)) {
        LOG_DEBUG(TIME, "1:%u 2:%u", time_stamp1, time_stamp2);
        float sec = difftime(time_stamp2, time_stamp1);
        diff_sec = (int32_t)sec;
    } else {
        print_time_date("Time1", date_time1, true);
        print_time_date("Time2", date_time2, true);
        LOG_ERROR(TIME, "Time1:%d Time2:%d", time_stamp1, time_stamp2);
    }
    return diff_sec;
}

#endif

bool time_init_one(uint8_t num) {
    bool res = true;
    const TimeConfig_t* Config = TimeGetConfig(num);
    if(Config) {
        TimeHandle_t* Node = TimeGetNode(num);
        if(Node) {
            Node->num = Config->num;
            Node->time_source = Config->time_source;
            Node->valid = true;
            Node->init_done = true;

            switch(Node->time_source) {
            case TIME_SRC_SYSTICK:
                break;
            case TIME_SRC_TIMER2:
                break;
#ifdef HAS_X86
            case TIME_SRC_WIN_CLOCK: {
                res = false;
                ftime(&start_time_b);
                res = true;
                LOG_INFO(TIME,
                         "time = %u.%03u, "
                         "timezone = %d, "
                         "dstflag = %d\n",
                         start_time_b.time, start_time_b.millitm, start_time_b.timezone, start_time_b.dstflag);

                struct tm* timeinfo;
                time(&start_time);
                timeinfo = localtime(&start_time);
                LOG_INFO(TIME, "start time local: %u [%s]", start_time, asctime(timeinfo));
                start_time_ms = start_time_b.millitm + start_time_b.time * 1000;

            } break;
#endif
            default:
                break;
            } // switch
        }
#ifdef HAS_LOG
        set_log_level(TIME, LOG_LEVEL_INFO);
#endif
    }
    return res;
}

#define CHOOSE_UP_TIME(UP_TIME, TIMER_TIME, SYSTICK_TIME)                                                              \
    do {                                                                                                               \
        if(0 == TIMER_TIME) {                                                                                          \
            if(0 == SYSTICK_TIME) {                                                                                    \
                UP_TIME += 2;                                                                                          \
            } else {                                                                                                   \
                UP_TIME = SYSTICK_TIME;                                                                                \
            }                                                                                                          \
        } else {                                                                                                       \
            UP_TIME = TIMER_TIME;                                                                                      \
        }                                                                                                              \
    } while(0);

uint32_t time_get_ms(uint8_t num) {
    static uint32_t time_ms = 0;
    TimeHandle_t* Node = TimeGetNode(num);
    if(Node) {
        switch(Node->time_source) {

#ifdef HAS_RISC_V
        case TIME_SRC_RISC_V: {
            time_ms = rv32imc_up_time_get_ms32();
        } break;
#endif

#ifdef HAS_SCR1_TIMER
        case TIME_SCR1_TIMER: {
            time_ms = scr1_timer_get_ms();
        } break;
#endif

#if defined(HAS_SYSTICK) && defined(HAS_NORTOS)
        case TIME_SRC_SYSTICK: {
            time_ms = systick_general_get_ms();
        } break;
#endif /*HAS_SYSTIC*/

#ifdef HAS_TIMER2
        case TIME_SRC_TIMER2: {
            time_ms = timer_get_ms(2);
        } break;
#endif

#ifdef HAS_PC
        case TIME_SRC_WIN_CLOCK: {
            time_ms = pc_clock_get_ms();
        } break;
#endif /*HAS_PC*/

#ifdef HAS_ZEPHYR
        case TIME_SRC_ZEPHYR_CLOCK: {
            time_ms = (uint32_t)k_uptime_get();
        } break;
#endif

#ifdef HAS_ESP32
        case TIME_SRC_ESP32_CLOCK: {
            time_ms = esp_time_get_ms32();
        } break;
#endif
        case TIME_SRC_SW_INCR: {
            time_ms++;
        } break;

        case TIME_SRC_RTC: {
        } break;

        default: {
            time_ms++;
        } break;
        }
    }

    return time_ms;
}

#ifdef HAS_TIME_EXT
float time_get_s(uint8_t num) {
    float up_time_s = 0;
    uint32_t up_time_ms = 0;
    up_time_ms = time_get_ms(num);
    up_time_s = ((float)up_time_ms) / 1000.0;
    return up_time_s;
}
#endif

uint32_t time_get_ms32(void) {
    uint32_t time_ms = 0;
    static bool recursion_protection = false;
    if(false == recursion_protection) {
        recursion_protection = true;
        time_ms = time_get_ms(TIME_MAIN_NUM);
        recursion_protection = false;
    }
    return time_ms;
}

#ifdef HAS_TIME_EXT

bool time_wait_timeout(uint32_t start_ms, uint32_t timeout_ms) {
    bool cycle = true;
    uint32_t cur_ms = time_get_ms32();
    uint32_t diff_ms = cur_ms - start_ms;
    if(timeout_ms < diff_ms) {
        cycle = false;
    }
    return cycle;
}
#endif

#ifdef HAS_TIME_EXT
uint32_t time_calc_duration_ms(uint32_t start_ms) {
    uint32_t duration_ms = 0;
    uint32_t time_end_ms = time_get_ms32();
    if(start_ms < time_end_ms) {
        duration_ms = time_end_ms - start_ms;
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(TIME, "End %u < Start %u Err", time_end_ms, start_ms);
#endif
    }
    return duration_ms;
}
#endif

#ifdef HAS_TIME_EXT
uint64_t time_get_ms64(void) {
    uint64_t time_ms = 0;
    static bool recursion_protection = false;
    if(false == recursion_protection) {
        recursion_protection = true;
        time_ms = time_get_us() / 1000;
        recursion_protection = false;
    }
    return time_ms;
}
#endif

uint64_t time_one_get_us(uint8_t num) {
    static uint64_t time_us = 0;
    bool res = false;
    (void)res;
    TimeHandle_t* Node = TimeGetNode(num);
    if(Node) {
        switch((uint32_t)Node->time_source) {
#ifdef HAS_RISC_V
        case TIME_SRC_RISC_V: {
            time_us = rv32imc_up_time_get_us();
        } break;
#endif

#ifdef HAS_SCR1_TIMER
        case TIME_SCR1_TIMER: {
            time_us = scr1_timer_get_us();
        } break;
#endif

#ifdef HAS_SYSTICK
        case TIME_SRC_SYSTICK: {
            time_us = systick_general_get_us();
        } break;
#endif /*HAS_SYSTIC*/

#ifdef HAS_TIMER2
        case TIME_SRC_TIMER2: {
            time_us = timer_get_us(2);
        } break;

#endif /*HAS_TIMER2*/

#ifdef HAS_TIMER5
        case TIME_SRC_TIMER5: {
            time_us = timer_get_us(5);
        } break;
#endif /*HAS_TIMER5*/

#ifdef HAS_PC
        case TIME_SRC_WIN_CLOCK: {
            time_us = pc_clock_get_us();
        } break;
#endif /*HAS_PC*/

#ifdef HAS_ZEPHYR
        case TIME_SRC_ZEPHYR_CLOCK: {
            time_us = (uint64_t)k_uptime_get() * 1000;

        } break;
#endif
        case TIME_SRC_SW_INCR: {
            time_us++;
        } break;

        case TIME_SRC_RTC: {

        } break;
        default: {
#ifdef HAS_MIK32
            res = time_fix();
#endif
        } break;
        }
    } else {
#ifdef HAS_MIK32
        res = time_fix();
#endif
    }

    return time_us;
}

uint64_t time_get_us(void) {
    uint64_t time_us = time_one_get_us(TIME_MAIN_NUM);
    return time_us;
}

#ifdef HAS_TIME_EXT
bool time_duration_init(DurationFsm_t* Duration) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(TIME, CRLF);
#endif
    if(Duration) {
        Duration->sec = 0;
        Duration->digit_f = 0.0;
        Duration->digit = 0;
        Duration->prev_char = ' ';
        Duration->fractional_cnt = 0;
#ifdef HAS_MATH
        Duration->part = DIGIT_INTEGER;
#endif
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_PARSE_8BIT_TYPES
static bool time_duration_parse_integer_digit(DurationFsm_t* Duration, char cur_ch) {
    bool res = true;
    uint8_t digit = char_to_u8(cur_ch);
    Duration->digit_f = Duration->digit_f * 10.0 + ((float)digit);
    return res;
}
#endif

#ifdef HAS_PARSE_8BIT_TYPES
static bool time_duration_parse_digit_fractional(DurationFsm_t* Duration, char cur_ch) {
    bool res = true;
    uint8_t digit = char_to_u8(cur_ch);
    // 5 ->0.5 1/2
    uint32_t base = ipow(10, Duration->fractional_cnt);
    float fraction = ((float)digit) / ((float)base);
#ifdef HAS_LOG
    LOG_DEBUG(TIME, "fraction + %f", fraction);
#endif
    Duration->digit_f += fraction;
    Duration->fractional_cnt++;
    return res;
}
#endif

#ifdef HAS_PARSE_8BIT_TYPES
static bool time_duration_parse_digit(DurationFsm_t* Duration, char cur_ch) {
    bool res = false;
    // LOG_DEBUG(TIME,"Cur digit %f",Duration->digit_f);
    switch(Duration->part) {
    case DIGIT_INTEGER:
        res = time_duration_parse_integer_digit(Duration, cur_ch);
        break;
    case DIGIT_FRACTIONAL:
        res = time_duration_parse_digit_fractional(Duration, cur_ch);
        break;
    default:
        res = false;
        break;
    }
    return res;
}
#endif

#ifdef HAS_PARSE_8BIT_TYPES
static bool time_duration_parse_one(DurationFsm_t* Duration, char cur_ch) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(TIME, "Proc [%c] Prev [%c] %f", cur_ch, Duration->prev_char, Duration->digit_f);
#endif
    if(Duration) {
        switch(cur_ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            res = time_duration_parse_digit(Duration, cur_ch);
            break;
        case ',':
        case '.':
            Duration->part = DIGIT_FRACTIONAL;
            Duration->fractional_cnt = 1;
            res = true;
            break;
        case 'h':
            Duration->digit_f = HOUR_2_SEC(Duration->digit_f);
            res = true;
            break;
        case 's':
            res = true;
            break;
        case 'm':
            Duration->digit_f = MIN_2_SEC(Duration->digit_f);
            res = true;
            break;
        case '\n':
        case '\r':
        case ' ':
            res = true;
            break;
        default:
            res = false;
            break;
        }
        Duration->prev_char = cur_ch;
    }
    return res;
}
#endif

#ifdef HAS_PARSE_8BIT_TYPES
uint32_t time_duration_parse(const char* const diration_str) {
    bool res = false;
    uint32_t sec = 0;
    DurationFsm_t Duration;
    res = time_duration_init(&Duration);
    if(res) {
        uint32_t len = strlen(diration_str);
        uint32_t i = 0;
        uint32_t ok_cnt = 0;

        for(i = 0; i < len; i++) {
            res = time_duration_parse_one(&Duration, diration_str[i]);
            if(res) {
                ok_cnt++;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(TIME, "Proc Ch[%u]=%c err", i, diration_str[i]);
#endif
            }
        }

        res = time_duration_parse_one(&Duration, '\n');
        if(res) {
            ok_cnt++;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TIME, "Proc CRLF err");
#endif
        }

        sec = (uint32_t)Duration.digit_f;
    }
    return sec;
}
#endif

#ifdef HAS_TIME_EXT
int calc_total_day_cnt(const struct tm* const date_time) {
    /*TODO Implement later*/
    return -1;
}
#endif

#ifdef HAS_PC
bool time_get_cur_utc(struct tm* const time_date) {
    bool res = false;
    if(time_date) {
        struct tm* utcTime = NULL;
        time_t tmi;
        time(&tmi);
        long int s_time;
        s_time = time(NULL);
        utcTime = gmtime(&s_time);
        if(utcTime) {
            utcTime->tm_year += 1900;
            res = is_valid_time_date(utcTime);
            if(res) {
                memcpy(time_date, utcTime, sizeof(struct tm));
                res = true;
            } else {
                LOG_ERROR(TIME, "InvalidTime");
                print_time_date("Invalid", utcTime, true);
            }
        } else {
            LOG_ERROR(TIME, "GetTimeErr");
        }
    }
    return res;
}
#endif

#ifdef HAS_PC
bool time_synchronize(void) {
    bool res = false;
    struct tm time_date;
    res = time_get_cur_utc(&time_date);
    if(res) {
        char lText[30] = {0};
        res = print_time_date("UTC:", &time_date, true);
#ifdef HAS_SERIAL
        res = is_target_connected();
#endif /*HAS_SERIAL*/
        if(res) {
            snprintf(lText, sizeof(lText), "dsst 1 %02u:%02u:%02u", time_date.tm_hour, time_date.tm_min,
                     time_date.tm_sec);
            LOG_INFO(TIME, "SetTime [%s]", lText);
#ifdef HAS_SERIAL
            res = cli_cmd_send(hComm, lText, strlen(lText));
#endif /*HAS_SERIAL*/

            snprintf(lText, sizeof(lText), "dssd 1 %s_%02u_%04u", TimeMonth2Str(time_date.tm_mon), time_date.tm_mday,
                     time_date.tm_year);
            LOG_INFO(TIME, "SetDate [%s]", lText);
#ifdef HAS_SERIAL
            res = cli_cmd_send(hComm, lText, strlen(lText));
#endif /*HAS_SERIAL*/
            /*
            dsst 1 02:16:00
            dssd 1 Jan_10_2022*/

        } else {
            LOG_ERROR(TIME, "TargetDisconnected");
        }

    } else {
        LOG_ERROR(TIME, "GetUTCTimeErr");
    }
    return res;
}
#endif

#ifdef HAS_TIME_EXT
bool time_uptime_2_time_date(uint32_t up_time, struct tm* const date_time) {
    bool res = false;
    if(date_time) {
        date_time->tm_sec = up_time % 60;
        date_time->tm_min = up_time / 60;
        date_time->tm_hour = up_time / 3600;
        res = true;
    }
    return res;
}
#endif





