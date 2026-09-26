#include "date_mcal.h"

#include <limits.h>
#include <stdlib.h> // Required for abs()

#include "std_includes.h"
#include "time_mcal.h"

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_STRING
#include "convert.h"
#endif

#ifdef HAS_DATA_MISC
#include "data_utils.h"
#endif

#ifdef HAS_STRING
#include "str_utils.h"
#endif

#ifdef HAS_CSV
#include "csv.h"
#endif



uint32_t calc_days_in_year(const struct tm* const date) {
    /*TODO*/
    return 365;
}


/* date in ddmmaa format */
bool parse_date_from_val(uint32_t packed_date, struct tm* tm_stamp) {
    bool res = false;
    if(tm_stamp) {
        res = true;
        tm_stamp->tm_mday = extract_digit(packed_date, 5) * 10 + extract_digit(packed_date, 4);
        if(32 <= tm_stamp->tm_mday) {
            res = false;
        }
        if(res) {
            tm_stamp->tm_mon =
                extract_digit(packed_date, 3) * 10 + extract_digit(packed_date, 2) - 1; /*Ublox count from 1*/
            if(13 <= tm_stamp->tm_mon) {
                res = false;
            }
        }

        if(res) {
            tm_stamp->tm_year = extract_digit(packed_date, 1) * 10 + extract_digit(packed_date, 0);
            tm_stamp->tm_year += 2000;
        }
    }
    return res;
}

 

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

bool is_time_date_equal(struct tm* date_time1, struct tm* date_time2) {
    bool res = true;
    if(res) {
        if(date_time1->tm_year == date_time2->tm_year) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_DEBUG(LG_DATE, "WrongYear %u %u", date_time1->tm_year, date_time2->tm_year);
#endif
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_mon == date_time2->tm_mon) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_DEBUG(LG_DATE, "WrongMon %u %u", date_time1->tm_mon, date_time2->tm_mon);
#endif
            res = false;
        }
    }
    if(res) {
        if(date_time1->tm_mday == date_time2->tm_mday) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongDay %u %u", date_time1->tm_mday, date_time2->tm_mday);
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_hour == date_time2->tm_hour) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongHour %u %u", date_time1->tm_hour, date_time2->tm_hour);
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_min == date_time2->tm_min) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongMin %u %u", date_time1->tm_min, date_time2->tm_min);
            res = false;
        }
    }

    if(res) {
        if(date_time1->tm_sec == date_time2->tm_sec) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongSec %u %u", date_time1->tm_sec, date_time2->tm_sec);
            res = false;
        }
    }

    return res;
}

bool is_valid_date(const struct tm* const date_time) {
    bool res = true;
    if(res) {
        /*TODO Rewise*/
        if((0 <= date_time->tm_year) && (date_time->tm_year < 2150)) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongYear %u", date_time->tm_year);
            res = false;
        }
    }
    if(res) {
        if((0 <= date_time->tm_mon) && (date_time->tm_mon <= 11)) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongMon %u", date_time->tm_mon);
            res = false;
        }
    }
    if(res) {
        if((1 <= date_time->tm_mday) && (date_time->tm_mday <= 31)) {
            res = true;
        } else {
            LOG_DEBUG(LG_DATE, "WrongDay %u", date_time->tm_mday);
            res = false;
        }
    }

    return res;
}


bool is_valid_time_date(const struct tm* const date_time) {
    bool res = true;

    res = is_valid_date(date_time);

    if(res) {
        res = is_valid_time(date_time);
    }

    return res;
}

/*Tue Dec  7 15:34:46 2021*/
bool time_data_parse(struct tm* date_time, char* str) {
    bool res = false;
    if(date_time && str) {
#ifdef HAS_RTC
        LOG_INFO(LG_DATE, "init time by [%s]", str);
#endif
        uint32_t cnt = 0;
        res = try_strl2int32(&str[17], 2, (int32_t*)&date_time->tm_sec);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, " ErrParse sec [%s]", &str[17]);
        }

        res = try_strl2int32(&str[14], 2, (int32_t*)&date_time->tm_min);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, " ErrParse min [%s]", &str[14]);
        }

        res = try_strl2int32(&str[11], 2, (int32_t*)&date_time->tm_hour);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, " ErrParse hour [%s]", &str[11]);
        }

        res = try_strl2month(&str[4], (int32_t*)&date_time->tm_mon);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, " ErrParse mon [%s]", &str[4]);
        }

        res = try_strl2int32(&str[8], 2, (int32_t*)&date_time->tm_mday);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, " ErrParse mday [%s]", &str[8]);
        }
        res = try_strl2int32(&str[20], 4, (int32_t*)&date_time->tm_year);
        if(res) {
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, " ErrParse year [%s]", &str[20]);
        }

        if(6 == cnt) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}


// 14.05.2025 Day:Month:Year
bool date_parse_rus(struct tm* const date_time, const char* const str) {
    bool res = false;
    if(date_time) {
        if(str) {
            LOG_DEBUG(LG_DATE, "ParseDateFrom:[%s]", str);
            // time_date_set_default(date_time);

            char token[20] = {0};
            uint32_t cnt = 0;
            uint32_t cnt_token = csv_cnt(str, '.');
            if(1 <= cnt_token) {
                res = csv_parse_text(str, '.', 0, token, sizeof(token));
                res = try_str2int32(token, (int32_t*)&date_time->tm_mday);
                if(res) {
                    cnt++;
                    LOG_DEBUG(LG_DATE, "ParseMonDay:%u", date_time->tm_mday);
                } else {
                    LOG_ERROR(LG_DATE, "ErrParseMonDay:[%s]", token);
                }
            }

            if(2 <= cnt_token) {
                res = csv_parse_text(str, '.', 1, token, sizeof(token));
                res = try_str2int32(token, (int32_t*)&date_time->tm_mon);
                if(res) {
                    cnt++;
                    date_time->tm_mon = date_time->tm_mon - 1;
                    LOG_DEBUG(LG_DATE, "ParseMon:%d", date_time->tm_mon);
                } else {
                    LOG_ERROR(LG_DATE, "ErrParseMon:[%s]", token);
                }
            }

            if(3 <= cnt_token) {
                res = csv_parse_text(str, '.', 2, token, sizeof(token));
                res = try_str2int32(token, (int32_t*)&date_time->tm_year);
                if(res) {
                    LOG_DEBUG(LG_DATE, "ParseYear:%d", date_time->tm_year);
                    cnt++;
                } else {
                    LOG_ERROR(LG_DATE, "ErrParse year [%s]", token);
                }
            }

            if(cnt) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

// Dec 21 2021
// Jan 10 2022
bool date_parse(struct tm* const date_time, const char* const str) {
    bool res = false;
    if(date_time && str) {
#ifdef HAS_RTC
        LOG_INFO(LG_DATE, "init time by [%s]", str);
#endif
        uint32_t cnt = 0;

#ifdef HAS_STR2_MONTH
        res = try_strl2month(&str[0], (int32_t*)&date_time->tm_mon);
        if(res) {
            cnt++;
            LOG_DEBUG(LG_DATE, "Parse mon %d", date_time->tm_mon);
        } else {
            LOG_ERROR(LG_DATE, "ErrParse mon [%s]", &str[0]);
        }
#endif

        res = try_strl2int32(&str[4], 2, (int32_t*)&date_time->tm_mday);
        if(res) {
            cnt++;
            LOG_DEBUG(LG_DATE, "Parse mday %u", date_time->tm_mday);
        } else {
            LOG_ERROR(LG_DATE, "ErrParse mday [%s]", &str[4]);
        }

        res = try_strl2int32(&str[7], 4, (int32_t*)&date_time->tm_year);
        if(res) {
            LOG_DEBUG(LG_DATE, "Parse year %d", date_time->tm_year);
            cnt++;
        } else {
            LOG_ERROR(LG_DATE, "ErrParse year [%s]", &str[7]);
        }

        if(3 == cnt) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

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
        LOG_DEBUG(LG_DATE, "1:%u 2:%u", time_stamp1, time_stamp2);
        float sec = (float)difftime(time_stamp2, time_stamp1);
        diff_sec = (int32_t)sec;
    } else {
        print_time_date("Time1", date_time1, true);
        print_time_date("Time2", date_time2, true);
        LOG_ERROR(LG_DATE, "Time1:%d Time2:%d", time_stamp1, time_stamp2);
    }
    return diff_sec;
}

#ifdef HAS_CALENDAR
int32_t time_calc_diff(struct tm* date_time1, struct tm* date_time2) {
    int32_t diff_s = 0;
    if(date_time1) {
        if(date_time2) {
            int32_t start = (int32_t)TimeDateToSeconds(date_time1);
            int32_t end = (int32_t)TimeDateToSeconds(date_time2);
            diff_s = end - start;
        }
    }
    return diff_s;
}
#endif



