#include "rtc_commands.h"

#include "common_diag.h"
#include "convert.h"
#include "log.h"
#include "rtc_mcal.h"
#include "str_utils.h"
#include "time_diag.h"
#include "time_mcal.h"

bool rtc_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = rtc_diag();
    } else {
        LOG_ERROR(LG_RTC, "Usage: rtd");
    }

    return res;
}

bool rtc_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    uint8_t num = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_RTC, "ParseErr TimerNum %s", argv[0]);
        }
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(LG_RTC, "ParseErr OnOff %s", argv[1]);
        }
    }

    if(res) {
        res = rtc_ctrl(num, on_off);
        if(res) {
            LOG_INFO(LG_RTC, "Set %u %s", num, OnOff2Str(on_off));
        } else {
            LOG_ERROR(LG_RTC, "Set %u %s", num, OnOff2Str(on_off));
        }
    } else {
        LOG_ERROR(LG_RTC, "Usage: rtc Num OnOff");
    }
    return res;
}

bool rtc_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        RtcHandle_t* Node = RtcGetNode(num);
        if(Node) {
            res = rtc_get(num, &Node->TimeDate);
            if(res) {
                LOG_INFO(LG_RTC, "RTC%u,%s", num, TimeDate2StrShort(&Node->TimeDate));
            } else {
                LOG_ERROR(LG_RTC, "Get,Err");
            }
        }
    } else {
        LOG_ERROR(LG_RTC, "Usage: rtg Num");
    }
    return res;
}

/*rsd 1 Jan_10_2022
 * rsd 1 Sep_17_2024
 * */
bool rtc_set_date_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    struct tm time_date_set;
    memset(&time_date_set, 0, sizeof(struct tm));
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_RTC, "Parse,Num [%s] Err", argv[0]);
        }

        char date_str[20] = "";
        strcpy(date_str, argv[1]);
        int ret = replace_char(date_str, '_', ' ');
        if(ret) {
            LOG_INFO(LG_RTC, "InText [%s]->[%s]", argv[1], date_str);
            res = date_parse(&time_date_set, date_str);
            if(res) {
                LOG_INFO(LG_RTC, "ParseDate [%s] Ok", date_str);
            } else {
                LOG_ERROR(LG_RTC, "Parse Date [%s] Err", date_str);
            }
        }
    }

    if(res) {
        res = rtc_set_date(num, &time_date_set);
    } else {
        LOG_ERROR(LG_RTC, "Usage: rsd Num Date");
        LOG_INFO(LG_RTC, "Example: rsd 1 Sep_16_2024");
    }
    return res;
}

/*
 rst 1 00:45:00
 rst 1 hh:mm:ss
 * */
bool rtc_set_time_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    struct tm time_date_set;
    memset(&time_date_set, 0, sizeof(struct tm));

    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_RTC, "Parse Num [%s] Err", argv[0]);
        }

        res = time_parse(&time_date_set, argv[1]);
        if(false == res) {
            LOG_ERROR(LG_RTC, "Parse Time [%s] Err", argv[1]);
        }
    }

    if(res) {
        res = rtc_set_time(num, &time_date_set);
    } else {
        LOG_ERROR(LG_RTC, "Usage: rst Num Time");
        LOG_INFO(LG_RTC, "Example: rst 1 hh:mm:ss");
    }
    return res;
}

bool rtc_adjust_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_RTC, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(res) {
        res = rtc_adjust_by_build_time(num);
    } else {
        LOG_ERROR(LG_RTC, "Usage: rta Num");
    }
    return res;
}
